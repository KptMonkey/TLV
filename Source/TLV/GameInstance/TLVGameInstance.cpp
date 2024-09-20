// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVGameInstance.h"

#include "MoviePlayer.h"

void UTLVGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this,&ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this,&ThisClass::OnDestinationWorldLoaded);
}

void UTLVGameInstance::OnPreLoadMap(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UTLVGameInstance::OnDestinationWorldLoaded(UWorld* LoadedWorld)
{
}

TSoftObjectPtr<UWorld> UTLVGameInstance::GetGameLevelByTag(FGameplayTag Tag) const
{
	for (const FTLVGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if(!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag == Tag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}
