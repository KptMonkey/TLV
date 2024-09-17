// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVCombatComponent.h"
#include "TLVEnemyCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TLV_API UTLVEnemyCombatComponent : public UTLVCombatComponent
{
	GENERATED_BODY()

public:
	virtual void OnHitTargetActor(AActor* TargetActor) override;
	virtual void OnPulledFromTargetActor(AActor* TargetActor) override;
};
