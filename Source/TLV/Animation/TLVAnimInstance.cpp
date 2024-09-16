// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAnimInstance.h"

#include "TLV/BlueprintFunctionLibrary/TLVBlueprintFunctionLibrary.h"
#include "TLV/Character/TLVCharacter.h"


bool UTLVAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (auto const OwningPawn = TryGetPawnOwner())
	{
		return UTLVBlueprintFunctionLibrary::NativeDoesActorHaveTag(OwningPawn,TagToCheck);
	}
	return false;
}
