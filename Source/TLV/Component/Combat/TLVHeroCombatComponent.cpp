// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "K2Node_SpawnActorFromClass.h"
#include "TLV/Actor/TLVMeleeWeapon.h"
#include "TLV/Assets/TLVGameplayTags.h"


ATLVMeleeWeapon* UTLVHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const
{
	return Cast<ATLVMeleeWeapon>(GetCarriedWeapon(WeaponTag));
}

ATLVMeleeWeapon* UTLVHeroCombatComponent::GetHeroEquippedWeapon() const
{
	return  Cast<ATLVMeleeWeapon>(GetEquippedWeapon());
}

float UTLVHeroCombatComponent::GetHeroEquippedWeaponDamageLevel(int Level) const
{
	return GetHeroEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(Level);
}

FGameplayTag UTLVHeroCombatComponent::DropCarriedWeapon()
{
	auto const CarriedWeapon = CarriedWeapons.Find(CarriedWeaponTag);
	if (!CarriedWeapon) return CarriedWeaponTag;
	
	CarriedWeapon->Get()->Destroy();
	CarriedWeapons.Empty();
	return CarriedWeaponTag;
}

void UTLVHeroCombatComponent::OnHitTargetActor(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor)) return;

	OverlappedActors.AddUnique(TargetActor);
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = TargetActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), TLVGameplayTags::Shared_Event_Melee_Hit, EventData);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), TLVGameplayTags::Player_Event_Hit_Pause, {});
}

void UTLVHeroCombatComponent::OnPulledFromTargetActor(AActor* TargetActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), TLVGameplayTags::Player_Event_Hit_Pause, {});
}

