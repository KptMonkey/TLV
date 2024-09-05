// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBlueprintFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"

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
