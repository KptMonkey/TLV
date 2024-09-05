// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVDataAssetStartupData.h"
#include "TLV/Common/TLVStructTypes.h"
#include "TLVDataAssetHeroStartUpData.generated.h"


/**
 * 
 */
UCLASS()
class TLV_API UTLVDataAssetHeroStartUpData : public UTLVDataAssetStartupData
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel) override;
private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData", meta = (TitleProperty="InputTag"))
	TArray<FTLVHeroAbilitySet> HeroStartUpAbilitySets;
	
};
