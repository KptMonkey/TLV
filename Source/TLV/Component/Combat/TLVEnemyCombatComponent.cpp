// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "TLV/Assets/TLVGameplayTags.h"

void UTLVEnemyCombatComponent::OnHitTargetActor(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor)) return;

	OverlappedActors.AddUnique(TargetActor);

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = false;
	const bool bIsMyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		
	}
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = TargetActor;
	if (bIsValidBlock)
	{
		
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), TLVGameplayTags::Shared_Event_Melee_Hit, EventData);
	}
	
}

void UTLVEnemyCombatComponent::OnPulledFromTargetActor(AActor* TargetActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Orange, "XXXXx");
}
