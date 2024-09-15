// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVGameplayAbility.h"
#include "TLV/Character/TLVCharacter.h"
#include "TLVHeroGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVHeroGameplayAbility : public UTLVGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	ATLVCharacter* GetHeroCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	ATLVPlayerController* GetHeroControllerFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	UTLVHeroCombatComponent* GetHeroCombatComponentFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLV | Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float WeaponBaseDamage, FGameplayTag CurrentAttackTag, int CurrentAttack);
private:
	TWeakObjectPtr<ATLVCharacter> CachedTLVHeroCharacter;
	TWeakObjectPtr<ATLVPlayerController> CachedTLVHeroController;
};