// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroCombatComponent.h"


ATLVMeleeWeapon* UTLVHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	return GetCarriedWeapon(WeaponTag);
}

