// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVDataAssetStartupData.h"
#include "TLVDataAssetEnemyStartUpData.generated.h"

class UTLVEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class TLV_API UTLVDataAssetEnemyStartUpData : public UTLVDataAssetStartupData
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="TLV | StartupData")
	TArray<TSubclassOf<UTLVEnemyGameplayAbility>> EnemyCombatGameplayAbilities;

};
