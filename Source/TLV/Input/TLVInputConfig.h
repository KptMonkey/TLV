// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "TLVInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FTLVInputAction
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = {};
};

/**
 * 
 */
UCLASS()
class TLV_API UTLVInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:

	UInputAction const* FindAbilityInputActionForTag(FGameplayTag const& GameplayTag, bool LogNotFound);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTLVInputAction> AbilityInputActions;
};
