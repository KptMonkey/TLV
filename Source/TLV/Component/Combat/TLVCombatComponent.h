// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TLV/Component/TLVBaseComponent.h"
#include "TLVCombatComponent.generated.h"

class ATLVMeleeWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TLV_API UTLVCombatComponent : public UTLVBaseComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= "Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, ATLVMeleeWeapon* WeaponToRegister, bool RegisterEquippedWeapon = false);
	UFUNCTION(BlueprintCallable, Category= "Combat")
	ATLVMeleeWeapon* GetCarriedWeapon(FGameplayTag WeaponTag) const;
	UPROPERTY(BlueprintReadWrite, Category= "Combat")
	FGameplayTag EquippedWeaponTag;
	UFUNCTION(BlueprintCallable, Category= "Combat")
	ATLVMeleeWeapon* GetEquippedWeapon()	const;
private:
	TMap<FGameplayTag, TObjectPtr<ATLVMeleeWeapon>> CarriedWeapons;
};
