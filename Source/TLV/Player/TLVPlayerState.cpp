// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVPlayerState.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"

ATLVPlayerState::ATLVPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTLVAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UTLVAttributeSet>("AttributeSet");
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ATLVPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
