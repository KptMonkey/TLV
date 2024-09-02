// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVBaseCharacter.h"
#include "TLV/Actor/TLVProjectileWeapon.h"
#include "TLV/Assets/TLVDataAssetInputConfig.h"
#include "TLV/Component/Combat/TLVHeroCombatComponent.h"
#include "TLVCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API ATLVCharacter : public ATLVBaseCharacter
{
	GENERATED_BODY()
public:
	ATLVCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void TraceUnderCrosshair(FHitResult& TraceHitResult);
	void Tick(float DeltaSeconds) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(BlueprintReadWrite, Replicated)
	FHitResult TraceHitResult;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat | Projectile Weapon")
	TObjectPtr<ATLVProjectileWeapon> ProjectileWeapon;
	UPROPERTY(ReplicatedUsing = OnRep_DefendsBiteAttempt)
	bool bDefendsBiteAttempt = false;
	UFUNCTION()
	void OnRep_DefendsBiteAttempt();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:
	virtual void InitAbilityComponent() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta = (AllowPrivateAccess=true))
	TObjectPtr<UTLVDataAssetInputConfig> InputConfigDataAsset;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat", meta = (AllowPrivateAccess=true))
	TObjectPtr<UTLVHeroCombatComponent> HeroCombatComponent = nullptr;

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);
public:
	FORCEINLINE TObjectPtr<UTLVHeroCombatComponent> GetCombatComponent() const
	{
		return HeroCombatComponent;
	}
};
