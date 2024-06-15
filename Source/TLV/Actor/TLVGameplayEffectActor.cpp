// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVGameplayEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
// Sets default values
ATLVGameplayEffectActor::ATLVGameplayEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void ATLVGameplayEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffect)
{
	auto const TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

	if (!TargetASC) return;
	
	auto GameplayEffectContextHandle = TargetASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	auto const EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffect, ActorLevel, GameplayEffectContextHandle);
	auto EffectSpec = EffectSpecHandle.Data.Get();
	if (EffectSpec)
	{
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
	}

}

// Called when the game starts or when spawned
void ATLVGameplayEffectActor::BeginPlay()
{
	Super::BeginPlay();
}


