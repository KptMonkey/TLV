// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVDataAssetEnemyStartUpData.h"
#include "TLV/AbilitySystem/Ability/TLVEnemyGameplayAbility.h"

void UTLVDataAssetEnemyStartUpData::GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(ASC, ApplyLevel);
	for (auto const& AbilityClass : EnemyCombatGameplayAbilities)
	{
		if (!AbilityClass) continue;
		
		FGameplayAbilitySpec AbilitySpec(AbilityClass);
		AbilitySpec.SourceObject = ASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		ASC->GiveAbility(AbilitySpec);
	}
}
