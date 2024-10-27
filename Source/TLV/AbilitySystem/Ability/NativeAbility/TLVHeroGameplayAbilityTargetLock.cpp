// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroGameplayAbilityTargetLock.h"

#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TLV/Assets/TLVGameplayTags.h"
#include "TLV/BlueprintFunctionLibrary/TLVBlueprintFunctionLibrary.h"

void UTLVHeroGameplayAbilityTargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                        const FGameplayEventData* TriggerEventData)
{
	TryLockOnTarget();
	InitTargetLockMappingContext();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UTLVHeroGameplayAbilityTargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMappingContext();
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UTLVHeroGameplayAbilityTargetLock::OnTargetLockTick(float DeltaTime)
{
	if (!CurrentLockedActor ||
	UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(CurrentLockedActor,TLVGameplayTags::Shared_Status_Death) ||
	UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), TLVGameplayTags::Shared_Status_Death)
	)
	{
		
		GetAvailableActorsToLock();
		TObjectPtr<AActor> NextTarget = nullptr;
		for (auto const Actor : AvailableActorsToLock)
		{
			if 	(UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(Actor,TLVGameplayTags::Shared_Status_Death)) continue;
			NextTarget = Actor;
			break;
		}
		if (!NextTarget)
		{
			CancelTargetLockAbility();
			ResetTargetLockMappingContext();
			CleanUp();
			return;
		}
			CurrentLockedActor = NextTarget;
	}

	const bool bShouldOverrideRotation = !UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(),TLVGameplayTags::Player_Status_Dodge);

	if (bShouldOverrideRotation)
	{
		 auto LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetHeroCharacterFromActorInfo()->GetActorLocation(),
			CurrentLockedActor->GetActorLocation()
		);

		LookAtRot -= FRotator(TargetOffsetDistance, 0.f, 0.f);
		const FRotator CurrentControlRot = GetHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot,LookAtRot,DeltaTime,TargetLockRotationInterpSpeed);

		GetHeroControllerFromActorInfo()->SetControlRotation(FRotator(TargetRot.Pitch,TargetRot.Yaw,0.f));
		GetHeroCharacterFromActorInfo()->SetActorRotation(FRotator(0.f,TargetRot.Yaw,0.f));
	}
}

void UTLVHeroGameplayAbilityTargetLock::SwitchTarget(FGameplayTag const& SwitchDirectionTag)
{
	TArray<TObjectPtr<AActor>> ActorsOnLeft;
	TArray<TObjectPtr<AActor>> ActorsOnRight;
	TObjectPtr<AActor> NewTargetToLock = nullptr;

	GetAvailableActorsAroundTarget(ActorsOnLeft,ActorsOnRight);

	if (SwitchDirectionTag == TLVGameplayTags::Player_Event_SwitchTarget_Left)
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnLeft);
	}
	else
	{
		NewTargetToLock = GetNearestTargetFromAvailableActors(ActorsOnRight);
	}

	if (NewTargetToLock)
	{
		CurrentLockedActor = NewTargetToLock;
	}
}

FVector UTLVHeroGameplayAbilityTargetLock::CalculateWarpTargetLocation(bool& IsValid)
{
	IsValid = false;
	if (!CurrentLockedActor) return {};

	if (!GetHeroCharacterFromActorInfo()) return {};

	IsValid = true;
	auto const HeroLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	auto const TargetLocation = CurrentLockedActor->GetActorLocation();

	auto const OffsetDirection = HeroLocation - TargetLocation;
	
	return OffsetDirection.GetSafeNormal() * WarpTargetLocationOffset + TargetLocation;
}

bool UTLVHeroGameplayAbilityTargetLock::IsInMotionWarpingDistance()
{
	if (!CurrentLockedActor) return false;
	auto const HeroLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	auto const TargetLocation = CurrentLockedActor->GetActorLocation();

	auto const HeroTargetDirection = HeroLocation - TargetLocation;
	return HeroTargetDirection.Length() < MotionWarpingDistance;
}

void UTLVHeroGameplayAbilityTargetLock::TryLockOnTarget()
{
	GetAvailableActorsToLock();
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	CurrentLockedActor = GetNearestTargetFromAvailableActors(AvailableActorsToLock);

	if (!CurrentLockedActor)
	{
		CancelTargetLockAbility();
	}
}

void UTLVHeroGameplayAbilityTargetLock::GetAvailableActorsToLock()
{
	AvailableActorsToLock.Empty();
	
	TArray<FHitResult> BoxTraceHits;
	auto const Character = GetHeroCharacterFromActorInfo(); 
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Character,
		Character->GetActorLocation(),
		Character->GetActorLocation() + Character->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		Character->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		{},
		bShowPersistentDebugShape? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);

	for (const FHitResult& TraceHit : BoxTraceHits)
	{
		if (AActor* HitActor = TraceHit.GetActor())
		{
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				AvailableActorsToLock.AddUnique(HitActor);
			}
		}
	}
}

TObjectPtr<AActor> UTLVHeroGameplayAbilityTargetLock::GetNearestTargetFromAvailableActors(const TArray<TObjectPtr<AActor>>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	return UGameplayStatics::FindNearestActor(GetHeroCharacterFromActorInfo()->GetActorLocation(),InAvailableActors,ClosestDistance);
}

void UTLVHeroGameplayAbilityTargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(),GetCurrentActorInfo(),GetCurrentActivationInfo(),true);
}

void UTLVHeroGameplayAbilityTargetLock::CleanUp()
{
	AvailableActorsToLock.Empty();
	CurrentLockedActor = nullptr;
}

void UTLVHeroGameplayAbilityTargetLock::ResetTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo()) return;
	auto const LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();

	auto const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem)

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

void UTLVHeroGameplayAbilityTargetLock::InitTargetLockMappingContext()
{
	if (!GetHeroControllerFromActorInfo()) return;
	auto const LocalPlayer = GetHeroControllerFromActorInfo()->GetLocalPlayer();

	auto const Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem)

	Subsystem->AddMappingContext(TargetLockMappingContext,3);
}

void UTLVHeroGameplayAbilityTargetLock::GetAvailableActorsAroundTarget(TArray<TObjectPtr<AActor>>& ActorsOnLeft,
	TArray<TObjectPtr<AActor>>& ActorsOnRight)
{
	if (!CurrentLockedActor || AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	const FVector PlayerLocation = GetHeroCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToCurrentNormalized = (CurrentLockedActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

	for (AActor* AvailableActor : AvailableActorsToLock)
	{
		if(!AvailableActor || AvailableActor == CurrentLockedActor) continue;

		const FVector PlayerToAvailableNormalized = (AvailableActor->GetActorLocation() - PlayerLocation).GetSafeNormal();

		const FVector CrossResult = FVector::CrossProduct(PlayerToCurrentNormalized,PlayerToAvailableNormalized);

		if (CrossResult.Z>0.f)
		{
			ActorsOnRight.AddUnique(AvailableActor);
		}
		else
		{
			ActorsOnLeft.AddUnique(AvailableActor);
		}
	}	
}
