// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroGameplayAbility.h"

ATLVCharacter* UTLVHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CachedTLVHeroCharacter.IsValid())
	{
		CachedTLVHeroCharacter = Cast<ATLVCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedTLVHeroCharacter.IsValid() ? CachedTLVHeroCharacter.Get() : nullptr;
}

ATLVPlayerController* UTLVHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CachedTLVHeroController.IsValid())
	{
		CachedTLVHeroController = Cast<ATLVPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedTLVHeroController.IsValid() ? CachedTLVHeroController.Get() : nullptr;
}

UTLVCombatComponent* UTLVHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetCombatComponent();
}
