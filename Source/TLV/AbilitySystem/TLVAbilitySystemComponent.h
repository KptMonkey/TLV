// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TLVAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer);
struct FTLVHeroAbilitySet;
/**
 * 
 */
UCLASS()
class TLV_API UTLVAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();
	void AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> const& GameplayAbilities);
	void RemoveCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> const& GameplayAbilities);
	void AbilityInputTagHeld(FGameplayTag const& InputTag);
	void AbilityInputTagReleasd(FGameplayTag const& InputTag);
	void TryActivateGameplayAbility();

	void OnAbilityInputPressed(FGameplayTag const& InputTag);
	void OnAbilityInputReleased(FGameplayTag const& InputTag);
	UFUNCTION(BlueprintCallable, Category= "TLV | Ability", meta = (ApplyLevel = "1"))
	void GrantHeroWeaponAbilities(TArray<FTLVHeroAbilitySet> const& DefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	UFUNCTION(BlueprintCallable, Category= "TLV | Ability", meta = (ApplyLevel = "1"))
	void RemoveGrantedHeroWeaponAbilites(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles);
protected:
	void EffectApplied(UAbilitySystemComponent* ASC, FGameplayEffectSpec const& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
public:
	FEffectAssetTags EffectAssetTags;
};
