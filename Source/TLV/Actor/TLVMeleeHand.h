// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVMeleeBase.h"
#include "TLVMeleeHand.generated.h"

class UBoxComponent;
UCLASS()
class TLV_API ATLVMeleeHand : public ATLVMeleeBase
{
	GENERATED_BODY()
public:
	ATLVMeleeHand();
	virtual void ToggleCollision(bool bEnable) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TLV | Weapon")
	TObjectPtr<UBoxComponent> HandCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual  void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
