// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCombatComponent.h"
#include "TLV/Actor/TLVMeleeWeapon.h"


void UTLVCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister,
	ATLVMeleeWeapon* WeaponToRegister, bool RegisterEquippedWeapon)
{
	checkf(!CarriedWeapons.Contains(WeaponTagToRegister), TEXT("Weapon already exist"));
	check(WeaponToRegister);
	CarriedWeapons.Emplace(WeaponTagToRegister, WeaponToRegister);

	WeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	WeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);
	if (RegisterEquippedWeapon)
	{
		EquippedWeaponTag = WeaponTagToRegister;
	}
	GEngine->AddOnScreenDebugMessage(-123123, 4, FColor::Green, "Register");
}

ATLVMeleeWeapon* UTLVCombatComponent::GetCarriedWeapon(FGameplayTag WeaponTag) const
{
	if (CarriedWeapons.Contains(WeaponTag))
	{
		// TODO Check out Unreal Maps
		auto const Weapon = CarriedWeapons.Find(WeaponTag);
		return *Weapon;
	}
	return nullptr;
}



ATLVMeleeWeapon* UTLVCombatComponent::GetEquippedWeapon() const
{
	if (!EquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCarriedWeapon(EquippedWeaponTag);
}

void UTLVCombatComponent::ToggleWeaponCollision(bool bEnable, EToggleDamageType ToggleDamageType)
{
	if (!bEnable)
	{
		OverlappedActors.Empty();
	}

	switch (ToggleDamageType)
	{
	case EToggleDamageType::CURRENT_EQUIPPED_WEAPON:
		{
			auto const Weapon = GetEquippedWeapon();
			check(Weapon);
			auto const CollisionEnabled = bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
			Weapon->GetWeaponCollisionBox()->SetCollisionEnabled(CollisionEnabled);
			break;
		}
	case EToggleDamageType::LEFT_HAND:
		break;
	case EToggleDamageType::RIGHT_HAND:
		break;
	}
}

void UTLVCombatComponent::OnHitTargetActor(AActor* TargetActor)
{
}

void UTLVCombatComponent::OnPulledFromTargetActor(AActor* TargetActor)
{
}
