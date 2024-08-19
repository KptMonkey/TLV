// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAssetManager.h"

#include "TLVGameplayTags.h"

UTLVAssetManager& UTLVAssetManager::Get()
{
	check(GEngine);
	
	auto const TLVAssetManager = Cast<UTLVAssetManager>(GEngine->AssetManager);
	return *TLVAssetManager;
}

void UTLVAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FTLVGameplayTags::InitializeNativeGameplayTags();
}