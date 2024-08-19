// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TLVAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UTLVAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};

