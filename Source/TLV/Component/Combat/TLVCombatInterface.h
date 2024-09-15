// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TLVCombatInterface.generated.h"

class UTLVCombatComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTLVCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TLV_API ITLVCombatInterface
{
	GENERATED_BODY()

public:
	virtual TObjectPtr<UTLVCombatComponent> GetCombatComponent() const = 0;
};
