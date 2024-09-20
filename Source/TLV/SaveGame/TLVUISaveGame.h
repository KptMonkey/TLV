// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TLV/Common/TLVStructTypes.h"
#include "TLVUISaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVUISaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FTLVGraphicSettings GraphicSettings;
	UPROPERTY(BlueprintReadOnly)
	int AntiAliasing = 1;
	UPROPERTY(BlueprintReadOnly)
	int ShadowQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int ShadingQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int TextureQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int ViewDistanceQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int VFXQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int FoliageQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int GIQuality = 1;
	UPROPERTY(BlueprintReadWrite)
	int ReflectionQuality = 1;
	
};
