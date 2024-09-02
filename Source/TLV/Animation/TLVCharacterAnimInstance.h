// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVAnimInstance.h"
#include "TLVCharacterAnimInstance.generated.h"

class ATLVCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class TLV_API UTLVCharacterAnimInstance : public UTLVAnimInstance
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

protected:
	
	
	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed = 0;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};
