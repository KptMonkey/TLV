// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TLV/Character/TLVCharacter.h"
#include "TLVAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaTime) override;
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category="Projectile Weapon")
	FTransform LeftHandTransform;
	UPROPERTY(BlueprintReadOnly, Category="Projectile Weapon")
	FVector AimOffset = {0.f, 0.f, 0.f};
	UPROPERTY(BlueprintReadOnly, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;
private:
	void CalculateTransformationToAttachLeftHandToWeapon();
	void UpdateProjectileWeaponAttributes();
	UPROPERTY()
	TObjectPtr<ATLVCharacter> Character = nullptr;
};
