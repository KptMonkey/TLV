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

	UFUNCTION(BlueprintCallable, Category="TLV")
	ATLVMeleeWeapon* GetHeroCarriedWeaponByTag(FGameplayTag WeaponTag) const;
};
