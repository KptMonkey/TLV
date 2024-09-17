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
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	ATLVEnemyCharacter* GetEnemyCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	UTLVEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, FScalableFloat const& DamageScalableFloat);
private:
	TWeakObjectPtr<ATLVEnemyCharacter> CachedTLVEnemyCharacter;
};
