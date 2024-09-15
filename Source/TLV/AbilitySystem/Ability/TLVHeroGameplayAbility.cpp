// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroGameplayAbility.h"

#include "TLV/Assets/TLVGameplayTags.h"

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

UTLVHeroCombatComponent* UTLVHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

FGameplayEffectSpecHandle UTLVHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> EffectClass, float WeaponBaseDamage, FGameplayTag CurrentAttackTag, int CurrentAttack)
{
	check(EffectClass);
	auto const ASC = GetTLVAbilitySystemComponentFromActorInfo();
	auto ContextHandle = ASC->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	
	auto const GameplayEffectSpecHandle = ASC->MakeOutgoingSpec(EffectClass, GetAbilityLevel(), ContextHandle);
	GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(TLVGameplayTags::Shared_SetByCaller_BaseDamage, WeaponBaseDamage);
	if (CurrentAttackTag.IsValid())
	{
		GameplayEffectSpecHandle.Data->SetSetByCallerMagnitude(CurrentAttackTag, CurrentAttack);
	}
	return GameplayEffectSpecHandle;
	
}
