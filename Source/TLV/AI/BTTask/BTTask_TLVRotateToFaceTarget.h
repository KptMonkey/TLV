﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TLVRotateToFaceTarget.generated.h"

// Thats how you can cache variables if stuff is not instanced
struct FRotateToFaceTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}

	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};
/**
 * 
 */
UCLASS()
class TLV_API UBTTask_TLVRotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_TLVRotateToFaceTarget();

	// UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	// UBTNode Interface
	virtual uint16 GetInstanceMemorySize() const override;
	// UBTNode Interface
	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	bool HasReachedAnglePrecision(APawn* QueryPawn,AActor* TargetActor) const;
	UPROPERTY(EditAnywhere, Category = "TLV | Face Target")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category = "TLV | Face Target")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category = "TLV | Face Target")
	FBlackboardKeySelector TargetToFaceKey;
};