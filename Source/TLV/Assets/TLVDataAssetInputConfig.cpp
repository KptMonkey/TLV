// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVDataAssetInputConfig.h"

TObjectPtr<UInputAction> UTLVDataAssetInputConfig::FindNativeInputActionByTag(FGameplayTag const& GameplayTag)
{
	for (auto const& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == GameplayTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
