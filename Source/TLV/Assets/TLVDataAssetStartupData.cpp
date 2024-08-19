// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVDataAssetStartupData.h"

void UTLVDataAssetStartupData::GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	checkf(ASC, TEXT("ASC is null!"));
	GrantAbilities(ActivateOnGivenAbilities, ASC, ApplyLevel);
	GrantAbilities(ReactiveAbilities, ASC, ApplyLevel);
}

void UTLVDataAssetStartupData::GrantAbilities(TArray<TSubclassOf<UTLVGameplayAbility>> AbilitiesToGive,
	UTLVAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	if (AbilitiesToGive.IsEmpty()) return;

	for (auto const& Ability : AbilitiesToGive)
	{
		if (!Ability) continue;
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = ASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		ASC->GiveAbility(AbilitySpec);
	}
}
