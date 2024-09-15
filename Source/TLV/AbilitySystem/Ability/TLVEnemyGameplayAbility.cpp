// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemyGameplayAbility.h"

#include "TLV/Character/TLVEnemyCharacter.h"

ATLVEnemyCharacter* UTLVEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedTLVEnemyCharacter.IsValid())
	{
		CachedTLVEnemyCharacter = Cast<ATLVEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedTLVEnemyCharacter.IsValid() ? CachedTLVEnemyCharacter.Get() : nullptr;
}

UTLVEnemyCombatComponent* UTLVEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	if (!GetEnemyCharacterFromActorInfo())
	{
		// TODO: Show Error Message
		return nullptr;
	}
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
