// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAbilitySystemComponent.h"

#include "Ability/TLVGameplayAbility.h"

void UTLVAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTLVAbilitySystemComponent::EffectApplied);
}

void UTLVAbilitySystemComponent::AddCharacterAbilities(TArray<TSubclassOf<UGameplayAbility>> const& GameplayAbilities)
{
	for (auto const& Ability : GameplayAbilities)
	{
		auto GameplayAbilitySpec = FGameplayAbilitySpec(Ability, 1);
		if (auto const TLVAbility = Cast<UTLVGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			GameplayAbilitySpec.DynamicAbilityTags.AddTag(TLVAbility->StartupInputTag);
		    GiveAbility(GameplayAbilitySpec);
		}
	}
}

void UTLVAbilitySystemComponent::RemoveCharacterAbilities(
	TArray<TSubclassOf<UGameplayAbility>> const& GameplayAbilities)
{
	for (auto const& Ability : GameplayAbilities)
	{
		auto GameplayAbilitySpec = FGameplayAbilitySpec(Ability, 1);
		if (auto const TLVAbility = Cast<UTLVGameplayAbility>(GameplayAbilitySpec.Ability))
		{
			GameplayAbilitySpec.DynamicAbilityTags.AddTag(TLVAbility->StartupInputTag);
			ClearAbility(GameplayAbilitySpec.Handle);
		}
	}
}

void UTLVAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag const& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		AbilitySpecInputPressed(AbilitySpec);
		if (AbilitySpec.IsActive()) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UTLVAbilitySystemComponent::AbilityInputTagReleasd(FGameplayTag const& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) continue;
		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UTLVAbilitySystemComponent::TryActivateGameplayAbility()
{
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UTLVAbilitySystemComponent::OnAbilityInputPressed(FGameplayTag const& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (auto const AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTag(InputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UTLVAbilitySystemComponent::OnAbilityInputReleased(FGameplayTag const& InputTag)
{
}

void UTLVAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC,
                                               FGameplayEffectSpec const& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);
	EffectAssetTags.Broadcast(GameplayTagContainer);
}
