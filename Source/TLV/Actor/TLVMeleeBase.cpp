// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVMeleeBase.h"



void ATLVMeleeBase::AssignGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle> const& AbilitySpecHandles)
{
	GrantedAbilitySpecHandles = AbilitySpecHandles;
}

TArray<FGameplayAbilitySpecHandle> ATLVMeleeBase::GetGrantedAbilitySpecHandles() const
{
	return GrantedAbilitySpecHandles;
}