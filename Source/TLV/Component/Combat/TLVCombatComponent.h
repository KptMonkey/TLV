// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TLV/Component/TLVBaseComponent.h"
#include "TLVCombatComponent.generated.h"

class ATLVMeleeWeapon;

UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	CURRENT_EQUIPPED_WEAPON,
	LEFT_HAND,
	RIGHT_HAND
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TLV_API UTLVCombatComponent : public UTLVBaseComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category= "TLV | Combat")
	void RegisterSpawnedWeapon(FGameplayTag WeaponTagToRegister, ATLVMeleeWeapon* WeaponToRegister, bool RegisterEquippedWeapon = false);
	UFUNCTION(BlueprintCallable, Category= "TLV | Combat")
	ATLVMeleeWeapon* GetCarriedWeapon(FGameplayTag WeaponTag) const;
	UPROPERTY(BlueprintReadWrite, Category= "TLV | Combat")
	FGameplayTag EquippedWeaponTag;
	UFUNCTION(BlueprintCallable, Category= "TLV | Combat")
	ATLVMeleeWeapon* GetEquippedWeapon() const;
	UFUNCTION(BlueprintCallable, Category= "TLV | Combat")
	void ToggleWeaponCollision(bool bEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CURRENT_EQUIPPED_WEAPON);
	virtual void OnHitTargetActor(AActor* TargetActor);
	virtual void OnPulledFromTargetActor(AActor* TargetActor);
protected:
	TArray<TObjectPtr<AActor>> OverlappedActors;
private:
	TMap<FGameplayTag, TObjectPtr<ATLVMeleeWeapon>> CarriedWeapons;
};
