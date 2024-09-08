// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVBaseCharacter.h"
#include "TLVEnemyCharacter.generated.h"

class UTLVEnemyCombatComponent;

UCLASS()
class TLV_API ATLVEnemyCharacter : public ATLVBaseCharacter
{
	GENERATED_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;
	// Sets default values for this character's properties
	ATLVEnemyCharacter();
	FORCEINLINE TObjectPtr<UTLVEnemyCombatComponent> GetCombatComponent() const
	{
		return EnemyCombatComponent;
	}
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "TLV | Combat")
	TObjectPtr<UTLVEnemyCombatComponent> EnemyCombatComponent = nullptr;
private:

	void InitEnemyStartUpData();
};
