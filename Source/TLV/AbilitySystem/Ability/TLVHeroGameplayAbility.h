// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVGameplayAbility.h"
#include "TLV/Character/TLVCharacter.h"
#include "TLVHeroGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVHeroGameplayAbility : public UTLVGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	ATLVCharacter* GetHeroCharacterFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	ATLVPlayerController* GetHeroControllerFromActorInfo();
	UFUNCTION(BlueprintPure, Category="TLVAbility")
	UTLVCombatComponent* GetHeroCombatComponentFromActorInfo();
private:
	TWeakObjectPtr<ATLVCharacter> CachedTLVHeroCharacter;
	TWeakObjectPtr<ATLVPlayerController> CachedTLVHeroController;
};