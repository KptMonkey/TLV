// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TLV/Common/TLVEnumTypes.h"
#include "TLV/Common/TLVStructTypes.h"
#include "TLVBlueprintFunctionLibrary.generated.h"

class UTLVGameInstance;
class UTLVCombatComponent;
class UTLVAbilitySystemComponent;




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

	static UTLVCombatComponent* NativeGetCombatComponentFromActor(AActor* Actor);
	UFUNCTION(BlueprintCallable, Category= "TLV | FunctionLibrary", meta = (DisplayName = "GetCombatComponentFromActor", ExpandEnumAsExecs = "ValidType"))
	static UTLVCombatComponent* BP_GetCombatComponentFromActor(AActor* Actor, ETLVValidType& ValidType);
	UFUNCTION(BlueprintPure, Category= "TLV | FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);
	UFUNCTION(BlueprintPure, Category = "TLV  | FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* Instigator, AActor* Target,float& OutAngleDifference);
	UFUNCTION(BlueprintPure, Category = "TLV  | FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UTLVGameInstance* GetTLVGameInstance(UObject* const WorldContextObject);
	/**
	 * 
	 * @param GraphicSettings 
	 */
	UFUNCTION(BlueprintCallable,Category = "Warrior|FunctionLibrary")
	static void SaveCurrentGraphicSetting(FTLVGraphicSettings GraphicSettings);

	UFUNCTION(BlueprintCallable,Category = "Warrior|FunctionLibrary")
	static bool TryLoadSavedGraphicSetting(FTLVGraphicSettings& GraphicSettings);
	UFUNCTION(BlueprintCallable,Category = "Warrior|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject,ETLVInputMode InputMode);
};
