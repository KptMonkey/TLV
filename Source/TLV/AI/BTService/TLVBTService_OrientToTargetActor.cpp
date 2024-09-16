// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBTService_OrientToTargetActor.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

UTLVBTService_OrientToTargetActor::UTLVBTService_OrientToTargetActor()
{
	NodeName = "Native Orient Rotation To Target Actor";
	INIT_SERVICE_NODE_NOTIFY_FLAGS();
	RotationInterpSpeed = 5.f;
	Interval = 0.f;
	RandomDeviation = 0.f;

	TargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, TargetActorKey), AActor::StaticClass());
	
}

void UTLVBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (auto const Blackboard = GetBlackboardAsset())
	{
		TargetActorKey.ResolveSelectedKey(*Blackboard);
	}
}

FString UTLVBTService_OrientToTargetActor::GetStaticDescription() const
{
	const FString Description = TargetActorKey.SelectedKeyName.ToString();
	return FString::Printf(TEXT("Orient roation to %s Key %s"), *Description, *GetStaticServiceDescription());
}

void UTLVBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto const TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetActorKey.SelectedKeyName));
	auto const OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (OwningPawn && TargetActor)
	{
		auto const LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
		auto const TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaSeconds, RotationInterpSpeed);
		OwningPawn->SetActorRotation(TargetRot);
	}
}
