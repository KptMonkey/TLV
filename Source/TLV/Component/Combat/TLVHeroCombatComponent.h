// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVCombatComponent.h"
#include "TLVHeroCombatComponent.generated.h"


class ATLVMeleeWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TLV_API UTLVHeroCombatComponent : public UTLVCombatComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="TLV | Combat")
	ATLVMeleeWeapon* GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const;
	UFUNCTION(BlueprintCallable, Category="TLV | Combat")
	ATLVMeleeWeapon* GetHeroEquippedWeapon() const;
	UFUNCTION(BlueprintCallable, Category="TLV | Combat")
	float GetHeroEquippedWeaponDamageLevel(int Level) const;
	UFUNCTION(BlueprintCallable, Category="TLV | Combat")
	FGameplayTag DropCarriedWeapon();
	virtual void OnHitTargetActor(AActor* TargetActor) override;
	virtual void OnPulledFromTargetActor(AActor* TargetActor) override;
	
};
