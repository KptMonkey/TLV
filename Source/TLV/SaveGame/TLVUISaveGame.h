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
	int AntiAliasing = 2;
	UPROPERTY(BlueprintReadOnly)
	int ShadowQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ShadingQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int TextureQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ViewDistanceQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int VFXQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int FoliageQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int GIQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ReflectionQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int FullScreen = 2;	
};
