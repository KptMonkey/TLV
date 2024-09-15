// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TLV/Common/TLVEnumTypes.h"
#include "TLV/Component/Combat/TLVCombatComponent.h"
#include "TLVGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ETLVAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

class UTLVAbilitySystemComponent;
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
	UPROPERTY(EditDefaultsOnly, Category="TLV | Ability")
	ETLVAbilityActivationPolicy AbilityActivationPolicy = ETLVAbilityActivationPolicy::OnTriggered;
	UFUNCTION(BlueprintPure, Category="TLV | Combat")
	UTLVCombatComponent* GetCombatComponentFromActorInfo() const;
	UFUNCTION(BlueprintPure, Category="TLV | ASC")
	UTLVAbilitySystemComponent* GetTLVAbilitySystemComponentFromActorInfo() const;
	UFUNCTION(BlueprintPure, Category="TLV| Mesh")
	USkeletalMeshComponent* GetVisibleMeshComponentFromActorInfo() const;	
	UFUNCTION(BlueprintPure, Category="TLV | Mesh")
	USkeletalMeshComponent* GetAnimatedMeshComponentFromActorInfo() const;
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,  FGameplayEffectSpecHandle const& GameplayEffectSpecHandle);
	UFUNCTION(BlueprintCallable, Category="TLV | Ability", meta = (DisplayName = "ApplyEffectSpecHandleToTargetActor", ExpandEnumAsExecs = "SuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,  FGameplayEffectSpecHandle const& GameplayEffectSpecHandle, ETLVSuccessType& SuccessType);

public:
	UPROPERTY(EditDefaultsOnly, Category="TLV | Input")
	FGameplayTag StartupInputTag;
};
