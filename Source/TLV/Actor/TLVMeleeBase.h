// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "TLVMeleeBase.generated.h"

DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)

/**
 * 
 */
UCLASS()
class TLV_API ATLVMeleeBase : public AActor
{
	GENERATED_BODY()

public:
	FOnTargetInteractedDelegate OnHitTarget;
	FOnTargetInteractedDelegate OnPulledFromTarget;

	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle> const& AbilitySpecHandles);
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;

protected:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
