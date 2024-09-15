// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "TLVGEExecCalc_DamageDealt.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVGEExecCalc_DamageDealt : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UTLVGEExecCalc_DamageDealt();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
