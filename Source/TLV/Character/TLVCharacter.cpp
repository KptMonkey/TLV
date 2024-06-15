// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TLV/Player/TLVPlayerController.h"
#include "TLV/Player/TLVPlayerState.h"
#include "TLV/UI/HUD/TLVHUD.h"

ATLVCharacter::ATLVCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void ATLVCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityComponent();
}

void ATLVCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityComponent();
}

void ATLVCharacter::InitAbilityComponent()
{
	auto const PlayerSate = GetPlayerState<ATLVPlayerState>();
	check(PlayerSate)

	AbilitySystemComponent = PlayerSate->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(PlayerSate, this);
	AttributeSet = PlayerSate->GetAttributeSet();
	auto text1 = FString("InitAbilityComponent");
	UE_LOG(LogTemp, Warning, TEXT("Health: %s"), *text1);

	if (auto const AuraPlayerController = Cast<ATLVPlayerController>(GetController()))
	{
		auto text2 = FString("InitAbilityComponent2");
		UE_LOG(LogTemp, Warning, TEXT("Health: %s"), *text2);
		
		if (auto const AuraHUD = Cast<ATLVHUD>(AuraPlayerController->GetHUD()))
		{
			auto text3 = FString("InitAbilityComponent3");
			UE_LOG(LogTemp, Warning, TEXT("Health: %s"), *text3);
			AuraHUD->InitOverlay(AuraPlayerController, PlayerSate, AbilitySystemComponent, AttributeSet);
		}
	}
}
