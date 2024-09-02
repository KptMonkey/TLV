// Fill out your copyright notice in the Description page of Project Settings.


#include "UTLVDataAssetHeroStartUp.h"



void UUTLVDataAssetHeroStartUp::GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(ASC, ApplyLevel);
	for (auto const& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = ASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		ASC->GiveAbility(AbilitySpec);
	}
}
