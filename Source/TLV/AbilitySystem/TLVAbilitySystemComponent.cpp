// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAbilitySystemComponent.h"

#include "Ability/TLVGameplayAbility.h"
#include "TLV/Assets/TLVGameplayTags.h"
#include "TLV/Common/TLVStructTypes.h"

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

		if (InputTag.MatchesTag(TLVGameplayTags::InputTag_Toggle))
		{
			if (AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UTLVAbilitySystemComponent::OnAbilityInputReleased(FGameplayTag const& InputTag)
{
}

void UTLVAbilitySystemComponent::GrantHeroWeaponAbilities(TArray<FTLVHeroAbilitySet> const& DefaultWeaponAbilities,
	int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (DefaultWeaponAbilities.IsEmpty()) return;

	for (auto const& WeaponAbility : DefaultWeaponAbilities)
	{
		if (!WeaponAbility.IsValid()) return;

		FGameplayAbilitySpec AbilitySpec(WeaponAbility.AbilityToGrant);
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.SourceObject = GetAvatarActor();
		AbilitySpec.DynamicAbilityTags.AddTag(WeaponAbility.InputTag);
		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
	}
}

void UTLVAbilitySystemComponent::RemoveGrantedHeroWeaponAbilites(TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles)
{
	if (AbilitySpecHandles.IsEmpty()) return;

	for (auto const& SpecHandle : AbilitySpecHandles)
	{
		if (!SpecHandle.IsValid()) continue;
		ClearAbility(SpecHandle);
	}
	AbilitySpecHandles.Empty();
}

bool UTLVAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTag)
{
	check(AbilityTag.IsValid());
	TArray<FGameplayAbilitySpec*> AbilitySpecs;
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTag.GetSingleTagContainer(), AbilitySpecs);
	if (AbilitySpecs.IsEmpty()) return false;

	auto const SpectoActivate = AbilitySpecs[0];
	check(SpectoActivate);

	if (!SpectoActivate->IsActive())
	{
		return TryActivateAbility(SpectoActivate->Handle);
	}
	return false;
}

void UTLVAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC,
                                               FGameplayEffectSpec const& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer GameplayTagContainer;
	GameplayEffectSpec.GetAllAssetTags(GameplayTagContainer);
	EffectAssetTags.Broadcast(GameplayTagContainer);
}
