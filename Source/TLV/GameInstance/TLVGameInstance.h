// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "TLVGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FTLVGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}


};
/**
 * 
 */
UCLASS()
class TLV_API UTLVGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
protected:
	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FTLVGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta =(GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag Tag) const;
};
