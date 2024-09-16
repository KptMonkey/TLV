// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"


ATLVAIController::ATLVAIController(FObjectInitializer const& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	SenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>("SenseConfigSight");
	SenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	SenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	SenseConfigSight->DetectionByAffiliation.bDetectNeutrals = false;
	SenseConfigSight->SightRadius = 5000.f;
	SenseConfigSight->LoseSightRadius = 0.f;
	SenseConfigSight->PeripheralVisionAngleDegrees = 180.f;

	CustomPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
	CustomPerceptionComponent->ConfigureSense(*SenseConfigSight);
	CustomPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	CustomPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}


ETeamAttitude::Type ATLVAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	auto const PawnToCheck = Cast<const APawn>(&Other);
	auto const OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}

void ATLVAIController::BeginPlay()
{
	Super::BeginPlay();
	if (auto CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
	}
}

void ATLVAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (auto const BlackBoard = GetBlackboardComponent())
		{
			BlackBoard->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
