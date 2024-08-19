// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/Ability/TLVGameplayAbility.h"
#include "TLVDataAssetStartupData.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVDataAssetStartupData : public UDataAsset
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UTLVAbilitySystemComponent * ASC, int32 ApplyLevel = 1);
protected:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UTLVGameplayAbility>> ActivateOnGivenAbilities; 
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UTLVGameplayAbility>> ReactiveAbilities;
	void GrantAbilities(TArray<TSubclassOf<UTLVGameplayAbility>> AbilitiesToGive, UTLVAbilitySystemComponent * ASC, int32 ApplyLevel = 1);
	
};
