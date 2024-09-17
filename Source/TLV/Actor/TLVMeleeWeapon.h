// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVMeleeBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TLV/Common/TLVStructTypes.h"
#include "TLVMeleeWeapon.generated.h"
UCLASS()
class TLV_API ATLVMeleeWeapon : public ATLVMeleeBase
{
	GENERATED_BODY()

public:
	ATLVMeleeWeapon();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual  void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapons")
	FTLVHeroWeaponData HeroWeaponData;
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() { return WeaponCollisionBox;}
	virtual void ToggleCollision(bool bEnable) override;
};
