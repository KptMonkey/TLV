// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/Component/Combat/TLVCombatComponent.h"
#include "TLVGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ETLVAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};
/**
 * 
 */
UCLASS()
class TLV_API UTLVGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	UPROPERTY(EditDefaultsOnly, Category="TLVAbility")
	ETLVAbilityActivationPolicy AbilityActivationPolicy = ETLVAbilityActivationPolicy::OnTriggered;
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	UTLVCombatComponent* GetCombatComponentFromActorInfo() const;
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	UTLVAbilitySystemComponent* GetTLVAbilitySystemComponentFromActorInfo() const;
public:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;
};
