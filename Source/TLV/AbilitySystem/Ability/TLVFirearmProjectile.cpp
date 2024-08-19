// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVFirearmProjectile.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TLV/Assets/TLVGameplayTags.h"
#include "TLV/Character/TLVCharacter.h"
#include "TLV/Player/TLVPlayerController.h"

void UTLVFirearmProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UTLVFirearmProjectile::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	
	if (auto const Player = Cast<ATLVCharacter>(GetAvatarActorFromActorInfo()))
	{
		if (!Player->Weapon) return;
		 FHitResult TraceHitResult;
		Player->TraceUnderCrosshair(TraceHitResult);
		//Player->bDefendsBiteAttempt = !Player->bDefendsBiteAttempt;
		//Player->OnRep_DefendsBiteAttempt();
//		GEngine->AddOnScreenDebugMessage(-9, 4, FColor::Green, TraceHitResult.Location.ToString());
//		GEngine->AddOnScreenDebugMessage(-7, 4, FColor::Green, TraceHitResult.ImpactPoint.ToString());
		GEngine->AddOnScreenDebugMessage(-9, 4, FColor::Orange, TraceHitResult.Location.ToString());
		

		const FVector SocketLocation = Player->Weapon->GetSocketLocation("SpawnProjectile");
		auto const SocketRotation = Player->Weapon->GetSocketRotation("SpawnProjectile");
		auto const TLocation = SocketLocation + SocketRotation.Quaternion().GetRightVector() * 100;
		
		
		auto const PlayerController = Cast<APlayerController>(Player->GetController());
		if (PlayerController == nullptr ) return;
		auto const TargetLocationn = TraceHitResult.bBlockingHit ? TraceHitResult.Location : TraceHitResult.ImpactPoint;
		FRotator Rotation = (TLocation - SocketLocation).Rotation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		auto const Projectile = GetWorld()->SpawnActorDeferred<ATLVProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());

		auto const GameplayTags = FTLVGameplayTags::Get();
		const float ScaledDamage = Damage.GetValueAtLevel(10);
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Damage, ScaledDamage);
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}

