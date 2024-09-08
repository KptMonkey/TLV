// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVGameplayAbility.h"
#include "TLVEnemyGameplayAbility.generated.h"

class UTLVEnemyCombatComponent;
class ATLVEnemyCharacter;
/**
 * 
 */
UCLASS()
class TLV_API UTLVEnemyGameplayAbility : public UTLVGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	ATLVEnemyCharacter* GetEnemyCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	UTLVEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
private:
	TWeakObjectPtr<ATLVEnemyCharacter> CachedTLVEnemyCharacter;
};
