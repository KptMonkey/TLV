// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemyCharacter.h"

#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TLV/Component/Combat/TLVEnemyCombatComponent.h"
#include "TLV/Assets/TLVDataAssetEnemyStartUpData.h"

void ATLVEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
	
}

// Sets default values
ATLVEnemyCharacter::ATLVEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 100.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UTLVEnemyCombatComponent>("EnemyCombatComponent");

}

void ATLVEnemyCharacter::InitEnemyStartUpData()
{
	if (StartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		StartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (auto LoadedData = StartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
				}
			}
			)
			);
}



