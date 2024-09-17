// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemyGameplayAbility.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/Assets/TLVGameplayTags.h"
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

FGameplayEffectSpecHandle UTLVEnemyGameplayAbility::MakeEnemyDamageSpecHandle(TSubclassOf<UGameplayEffect> EffectClass,
	FScalableFloat const& DamageScalableFloat)
{
	check(EffectClass);
	auto const ASC = GetTLVAbilitySystemComponentFromActorInfo();
	auto ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	auto const GameplayEffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);

	GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(TLVGameplayTags::Shared_SetByCaller_BaseDamage, DamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));

	return GameplayEffectSpecHandle;
}
