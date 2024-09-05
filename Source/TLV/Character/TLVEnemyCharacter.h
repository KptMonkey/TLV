// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVBaseCharacter.h"
#include "TLVEnemyCharacter.generated.h"

UCLASS()
class TLV_API ATLVEnemyCharacter : public ATLVBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATLVEnemyCharacter();
	virtual void BeginPlay() override;
private:
	virtual void InitAbilityComponent() override;

};
