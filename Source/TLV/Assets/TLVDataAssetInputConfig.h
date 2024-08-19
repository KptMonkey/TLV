// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "TLV/Player/TLVPlayerController.h"
#include "TLVDataAssetInputConfig.generated.h"


USTRUCT(BlueprintType)
struct FTLVInputActionConfig
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;
};

/**
 * 
 */
UCLASS()
class TLV_API UTLVDataAssetInputConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty= "InputTag"))
	TArray<FTLVInputActionConfig> NativeInputActions;

	TObjectPtr<UInputAction> FindNativeInputActionByTag(FGameplayTag const& GameplayTag);
};
