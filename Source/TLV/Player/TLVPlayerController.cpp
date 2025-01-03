﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TLV/Input/TLVInputComponent.h"

ATLVPlayerController::ATLVPlayerController()
{
}

void ATLVPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

FGenericTeamId ATLVPlayerController::GetGenericTeamId() const
{
	return TeamId;
}

void ATLVPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(TLVContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!Subsystem) return;
	Subsystem->AddMappingContext(TLVContext, 0);
	/*
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	*/
	}

void ATLVPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}

void ATLVPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
}

void ATLVPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagReleasd(InputTag);
	
}

void ATLVPlayerController::ABilityInputTagHeld(FGameplayTag InputTag)
{
	if (!GetASC()) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

void ATLVPlayerController::Move(const FInputActionValue& InputActionValue)
{
	/*
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	*/
}

TObjectPtr<UTLVAbilitySystemComponent> ATLVPlayerController::GetASC()
{
	if (!TLVAbilitySystemComponent)
	{
		TLVAbilitySystemComponent = Cast<UTLVAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return TLVAbilitySystemComponent;
}
