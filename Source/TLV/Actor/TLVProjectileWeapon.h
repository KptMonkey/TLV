// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLVProjectileWeapon.generated.h"

UCLASS()
class TLV_API ATLVProjectileWeapon : public AActor
{
	GENERATED_BODY()

public:
	ATLVProjectileWeapon();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon | Properties")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon | Animation")
	FVector AimOffset = {0.f, 0.f, 0.f};
};
