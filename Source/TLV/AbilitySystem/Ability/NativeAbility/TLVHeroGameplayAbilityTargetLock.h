// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLV/AbilitySystem/Ability/TLVHeroGameplayAbility.h"
#include "TLVHeroGameplayAbilityTargetLock.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVHeroGameplayAbilityTargetLock : public UTLVHeroGameplayAbility
{
	GENERATED_BODY()
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};