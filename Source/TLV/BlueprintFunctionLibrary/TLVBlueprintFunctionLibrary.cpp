// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/Assets/TLVGameplayTags.h"
#include "TLV/Component/Combat/TLVCombatInterface.h"

TObjectPtr<UTLVAbilitySystemComponent> UTLVBlueprintFunctionLibrary::NativeGetTLVASCFromActor(
	TObjectPtr<AActor> Actor)
{
	check(Actor)

	return CastChecked<UTLVAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Actor));
}

void UTLVBlueprintFunctionLibrary::AddGameplayTagToActor(AActor* Actor, FGameplayTag TagToAdd)
{
	auto const ASC = NativeGetTLVASCFromActor(Actor);
	if (ASC->HasMatchingGameplayTag(TagToAdd)) return;

	ASC->AddLooseGameplayTag(TagToAdd);
}

void UTLVBlueprintFunctionLibrary::RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag TagToRemove)
{
	auto const ASC = NativeGetTLVASCFromActor(Actor);
	if (!ASC->HasMatchingGameplayTag(TagToRemove)) return;

	ASC->RemoveLooseGameplayTag(TagToRemove);
}

bool UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck)
{
	auto const ASC = NativeGetTLVASCFromActor(Actor);
	return ASC->HasMatchingGameplayTag(TagToCheck); 
}

void UTLVBlueprintFunctionLibrary::BP_DoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck, ETLVConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(Actor, TagToCheck) ? ETLVConfirmType::YES : ETLVConfirmType::NO;
}

UTLVCombatComponent* UTLVBlueprintFunctionLibrary::NativeGetCombatComponentFromActor(AActor* Actor)
{
	check(Actor);
	if (auto const CombatComponentInterface = Cast<ITLVCombatInterface>(Actor))
	{
		return CombatComponentInterface->GetCombatComponent();
	}
	return nullptr;
}

UTLVCombatComponent* UTLVBlueprintFunctionLibrary::BP_GetCombatComponentFromActor(AActor* Actor,
	ETLVValidType& ValidType)
{
	auto const CombatComponent =  NativeGetCombatComponentFromActor(Actor);
	ValidType = CombatComponent ? ETLVValidType::VALID : ETLVValidType::INVALID;
	return CombatComponent;
}

bool UTLVBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	auto const QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	auto const TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());
	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

FGameplayTag UTLVBlueprintFunctionLibrary::ComputeHitReactDirectionTag(AActor* Instigator, AActor* Target,
	float& OutAngleDifference)
{
	check(Instigator && Target);

	const FVector TargetForward = Target->GetActorForwardVector();
	const FVector InstigatorToAttackerNormalized = (Instigator->GetActorLocation() - Instigator->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(TargetForward,InstigatorToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(TargetForward,InstigatorToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference>=-45.f && OutAngleDifference <=45.f)
	{
		return TLVGameplayTags::Shared_Event_HitReact_Light_Front_Head;
	}
	else if (OutAngleDifference<-45.f && OutAngleDifference>=-135.f)
	{
		return TLVGameplayTags::Shared_Event_HitReact_Light_Left_Head_Down;
	}
	else if (OutAngleDifference<-135.f || OutAngleDifference>135.f)
	{
		return TLVGameplayTags::Shared_Event_HitReact_Light_Right_Head_Down;
	}
	else if(OutAngleDifference>45.f && OutAngleDifference<=135.f)
	{
		return TLVGameplayTags::Shared_Event_HitReact_Light_Right_Head_Down;
	}

	return TLVGameplayTags::Shared_Event_HitReact_Light_Front_Head;
}
