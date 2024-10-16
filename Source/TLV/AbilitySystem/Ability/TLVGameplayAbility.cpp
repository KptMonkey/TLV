﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "TLV/Character/TLVCharacter.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"

void UTLVGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                     const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                     bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (AbilityActivationPolicy == ETLVAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

void UTLVGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (AbilityActivationPolicy == ETLVAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

UTLVCombatComponent* UTLVGameplayAbility::GetCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UTLVCombatComponent>();
}

UTLVAbilitySystemComponent* UTLVGameplayAbility::GetTLVAbilitySystemComponentFromActorInfo() const
{
	return Cast<UTLVAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

USkeletalMeshComponent* UTLVGameplayAbility::GetVisibleMeshComponentFromActorInfo() const
{
	return Cast<ATLVCharacter>(GetAvatarActorFromActorInfo())->GetVisibleMesh();
}

USkeletalMeshComponent* UTLVGameplayAbility::GetAnimatedMeshComponentFromActorInfo() const
{
	return Cast<ATLVCharacter>(GetAvatarActorFromActorInfo())->GetAnimatedMesh();
}

FActiveGameplayEffectHandle UTLVGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,
	FGameplayEffectSpecHandle const& GameplayEffectSpecHandle)
{
	auto const TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	check(TargetASC)
	return GetTLVAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data, TargetASC);
}

FActiveGameplayEffectHandle UTLVGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	FGameplayEffectSpecHandle const& GameplayEffectSpecHandle, ETLVSuccessType& SuccessType)
{
	auto const Handle = NativeApplyEffectSpecHandleToTarget(TargetActor, GameplayEffectSpecHandle);
	SuccessType = Handle.WasSuccessfullyApplied() ? ETLVSuccessType::Success : ETLVSuccessType::Failed;
	return Handle;
}
