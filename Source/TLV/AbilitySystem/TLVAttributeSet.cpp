// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAttributeSet.h"

#include <string>

#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "TLV/Assets/TLVGameplayTags.h"
#include "TLV/BlueprintFunctionLibrary/TLVBlueprintFunctionLibrary.h"


UTLVAttributeSet::UTLVAttributeSet()
{
	InitMaxHealth(100);
	InitHealth(100);
	InitAttackPower(16);
	InitDamageTaken(0);
	InitDefensePower(10);
}

void UTLVAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTLVAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTLVAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTLVAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UTLVAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		const float NewHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
		SetHealth(NewHealth);
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		auto const NewHealth = FMath::Clamp(GetHealth() - GetDamageTaken(), 0.f, GetMaxHealth());
		SetHealth(NewHealth);
		if (GetHealth() == 0.f)
		{
			UTLVBlueprintFunctionLibrary::AddGameplayTagToActor(Data.Target.GetAvatarActor(), TLVGameplayTags::Shared_Status_Death);
		}
	}
	
}

void UTLVAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTLVAttributeSet, Health, OldHealth);
}

void UTLVAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTLVAttributeSet, MaxHealth, OldMaxHealth);
}

void UTLVAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
	FEffectProperties& EffectProperties)
{
	auto EffectConextHandle = Data.EffectSpec.GetContext();
	auto InstigatorASC = EffectConextHandle.GetOriginalInstigatorAbilitySystemComponent();
	UE_LOG(LogTemp, Warning, TEXT("InstigatorASC: %s"), *InstigatorASC->GetName());

	if (!InstigatorASC && InstigatorASC->AbilityActorInfo) return;
	EffectProperties.SourceASC = InstigatorASC;
	
	EffectProperties.SourceAvatarActor = InstigatorASC->AbilityActorInfo->AvatarActor.Get();
	AController* InstigatorPlayerController = InstigatorASC->AbilityActorInfo->PlayerController.Get();
	if (!InstigatorPlayerController && EffectProperties.SourceAvatarActor)
	{
		if (auto Pawn = Cast<APawn>(EffectProperties.SourceAvatarActor))
		{
			EffectProperties.SourceController = Pawn->GetController();
		}
	}
	if (InstigatorPlayerController)
	{
	 auto Pawn	=  Cast<ACharacter>(InstigatorPlayerController->GetPawn());
	}

	if ( Data.Target.AbilityActorInfo && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		EffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		UE_LOG(LogTemp, Warning, TEXT("TargetAvatarActor: %s"), *EffectProperties.TargetAvatarActor->GetName());

		EffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		auto TargetCharacter = Cast<ACharacter>(EffectProperties.TargetAvatarActor);
		EffectProperties.TargetASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
		
	}
}

