// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TLVBlueprintFunctionLibrary.generated.h"

class UTLVAbilitySystemComponent;

UENUM()
enum class ETLVConfirmType : uint8
{
	YES,
	NO
};
/**
 * 
 */
UCLASS()
class TLV_API UTLVBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static TObjectPtr<UTLVAbilitySystemComponent> NativeGetTLVASCFromActor(TObjectPtr<AActor> Actor);
	UFUNCTION(BlueprintCallable, Category= "TLV | FunctionLibrary")
	static void AddGameplayTagToActor(AActor* Actor, FGameplayTag TagToAdd);
	UFUNCTION(BlueprintCallable, Category= "TLV | FunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* Actor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck);
	UFUNCTION(BlueprintCallable, Category= "TLV | FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* Actor, FGameplayTag TagToCheck, ETLVConfirmType& OutConfirmType);
	
};
