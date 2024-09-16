// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TLVBTService_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVBTService_OrientToTargetActor : public UBTService
{
	GENERATED_BODY()
	
	UTLVBTService_OrientToTargetActor();
	// UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	// UBTNode Interface
	virtual FString GetStaticDescription() const override;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	UPROPERTY(EditAnywhere, Category="TLV | Target")
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere, Category="TLV | Target")
	float RotationInterpSpeed;
};
