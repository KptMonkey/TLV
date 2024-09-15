// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
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
