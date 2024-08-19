// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVInputConfig.h"

UInputAction const* UTLVInputConfig::FindAbilityInputActionForTag(FGameplayTag const& GameplayTag, bool LogNotFound)
{
	for (auto const& InputAction : AbilityInputActions)
	{
		if (InputAction.InputAction && InputAction.InputTag == GameplayTag) return InputAction.InputAction;
	}

	if (LogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find InputAction for Tag"));
	}
	return nullptr;
}
