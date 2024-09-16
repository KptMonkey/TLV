// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "TLVAIController.generated.h"

UCLASS()
class TLV_API ATLVAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATLVAIController(FObjectInitializer const& ObjectInitializer);
	// IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> CustomPerceptionComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> SenseConfigSight;

	UFUNCTION()
	virtual  void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
