// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "TLVGameplayEffectActor.generated.h"

UCLASS()
class TLV_API ATLVGameplayEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATLVGameplayEffectActor();
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor * Target, TSubclassOf<UGameplayEffect> GameplayEffect);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	float ActorLevel = 1;
};
