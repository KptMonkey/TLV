// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVDataAssetStartupData.h"
#include "UTLVDataAssetHeroStartUp.generated.h"

USTRUCT(BlueprintType)
struct FTLVHeroAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UTLVGameplayAbility> AbilityToGrant;
	bool IsValid() const;

};

/**
 * 
 */
UCLASS()
class TLV_API UUTLVDataAssetHeroStartUp : public UTLVDataAssetStartupData
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UTLVAbilitySystemComponent* ASC, int32 ApplyLevel) override;
private:
	UPROPERTY(EditDefaultsOnly, Category="StartupData", meta = (TitleProperty="InputTag"))
	TArray<FTLVHeroAbilitySet> HeroStartUpAbilitySets;
	
};
