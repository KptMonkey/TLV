// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVBaseCharacter.h"
#include "TLVCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API ATLVCharacter : public ATLVBaseCharacter
{
	GENERATED_BODY()
public:
	ATLVCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityComponent();
};
