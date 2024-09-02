// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVHeroAnimInstance.h"
#include "TLV/Animation/TLVAnimInstance.h"
#include "TLVHeroLinkedAnimLayer.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVHeroLinkedAnimLayer : public UTLVAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UTLVHeroAnimInstance* GetHeroAnimInstance() const;
};
