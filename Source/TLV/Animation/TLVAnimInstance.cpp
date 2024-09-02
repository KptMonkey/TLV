// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAnimInstance.h"

#include "TLV/Character/TLVCharacter.h"


bool UTLVAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		//return UWarriorFunctionLibrary::NativeDoesActorHaveTag(OwningPawn,TagToCheck);
	}

	return false;
}
