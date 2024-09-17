// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCombatComponent.h"

#include "TLV/Actor/TLVMeleeHand.h"
#include "TLV/Actor/TLVMeleeWeapon.h"
#include "TLV/Assets/TLVGameplayTags.h"


void UTLVCombatComponent::RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister,
                                                ATLVMeleeWeapon* WeaponToRegister, bool RegisterEquippedWeapon)
{
	checkf(!CarriedWeapons.Contains(WeaponTagToRegister), TEXT("Weapon already exist"));
	check(WeaponToRegister);
	CarriedWeapons.Emplace(WeaponTagToRegister, WeaponToRegister);

	WeaponToRegister->OnHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	WeaponToRegister->OnPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);
	if (RegisterEquippedWeapon)
	{
		EquippedWeaponTag = WeaponTagToRegister;
	}
}

void UTLVCombatComponent::RegisterHand(FGameplayTag HandTagToRegister, ATLVMeleeHand* HandToRegister)
{
	checkf(!Hands.Contains(HandTagToRegister), TEXT("Weapon already exist"));
	check(HandToRegister);
	Hands.Emplace(HandTagToRegister, HandToRegister);

	HandToRegister->OnHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
	HandToRegister->OnPulledFromTarget.BindUObject(this, &ThisClass::OnPulledFromTargetActor);
}

ATLVMeleeHand* UTLVCombatComponent::GetHand(FGameplayTag HandTag) const
{
	if (Hands.Contains(HandTag))
	{
		auto const Hand = Hands.Find(HandTag);
		return * Hand;
	}
	return nullptr;
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
		{
			auto const LeftHand = GetHand(TLVGameplayTags::Enemy_Weapon_LeftHand);
			LeftHand->ToggleCollision(bEnable);
			break;
			
		}
	case EToggleDamageType::RIGHT_HAND:
		{
			auto const RightHand = GetHand(TLVGameplayTags::Enemy_Weapon_RightHand);
			RightHand->ToggleCollision(bEnable);
			break;
		}
	}
}

void UTLVCombatComponent::OnHitTargetActor(AActor* TargetActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Orange, "XXXXx");
}

void UTLVCombatComponent::OnPulledFromTargetActor(AActor* TargetActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Orange, "XXXXx");
}
