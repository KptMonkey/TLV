// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"
#include "TLV/Input/TLVInputComponent.h"
#include "TLV/Player/TLVPlayerController.h"
#include "TLV/Player/TLVPlayerState.h"
#include "TLV/UI/HUD/TLVHUD.h"
#include "TLV/Assets/TLVDataAssetHeroStartUpData.h"
#include "TLV/Assets/TLVGameplayTags.h"

ATLVCharacter::ATLVCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	HeroCombatComponent = CreateDefaultSubobject<UTLVHeroCombatComponent>("CombatComponent");
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,500.f,0.f);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

void ATLVCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityComponent();
	AddCharacterAbilities();
	if (!StartUpData.IsNull())
	{
		auto const LoadedData = StartUpData.LoadSynchronous();
		LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);
	}
}

void ATLVCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityComponent();
}

void ATLVCharacter::TraceUnderCrosshair(FHitResult& HitResult)
{
	auto const TLVPlayerController = Cast<ATLVPlayerController>(GetController());
	if (!TLVPlayerController) return;
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
	FVector CrosshairWorldPos;
	FVector CrosshairWorldDir;
	 
	bool const bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(TLVPlayerController, CrosshairLocation, CrosshairWorldPos, CrosshairWorldDir);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-99, 4, FColor::Green, CrosshairLocation.ToString());
		GEngine->AddOnScreenDebugMessage(-98, 4, FColor::Green, CrosshairWorldPos.ToString());
		
	}


	if (true)
	{
		//auto const Start = CrosshairWorldPos;
		//auto const End = Start + CrosshairWorldDir * 100000.f;
		 auto const Start = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
		 auto const End = Start + GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector() * 100000.f;
		if (!GetWorld()) return;
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);
		if (!HitResult.bBlockingHit)
		{
			HitResult.ImpactPoint = End;
		}
	}
}

void ATLVCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//	TraceUnderCrosshair(TraceHitResult);
	//	OnRep_DefendsBiteAttempt();
}

void ATLVCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATLVCharacter, TraceHitResult);
	DOREPLIFETIME(ATLVCharacter, bDefendsBiteAttempt);

}

void ATLVCharacter::OnRep_DefendsBiteAttempt()
{
	TraceUnderCrosshair(TraceHitResult);
	GEngine->AddOnScreenDebugMessage(-198, 4, FColor::Blue, TraceHitResult.Location.ToString());

}

void ATLVCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Add input config data asset to the blueprint"))
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	auto const LocalPlayer = GetController<ATLVPlayerController>()->GetLocalPlayer();
	auto const SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(SubSystem);
	SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	auto TLVInputComponent = CastChecked<UTLVInputComponent>(PlayerInputComponent);

	TLVInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	TLVInputComponent->BindNativeInputAction(InputConfigDataAsset,TLVGameplayTags::InputTag_Move,ETriggerEvent::Triggered,this,&ThisClass::Input_Move);
	TLVInputComponent->BindNativeInputAction(InputConfigDataAsset,TLVGameplayTags::InputTag_Look,ETriggerEvent::Triggered,this,&ThisClass::Input_Look);

	TLVInputComponent->BindNativeInputAction(InputConfigDataAsset,TLVGameplayTags::InputTag_SwitchTarget,ETriggerEvent::Triggered,this,&ThisClass::Input_SwitchTargetTriggered);
	TLVInputComponent->BindNativeInputAction(InputConfigDataAsset,TLVGameplayTags::InputTag_SwitchTarget,ETriggerEvent::Completed,this,&ThisClass::Input_SwitchTargetCompleted);

}

TObjectPtr<UTLVCombatComponent> ATLVCharacter::GetCombatComponent() const
{
	return HeroCombatComponent;
}

void ATLVCharacter::InitAbilityComponent()
{
	auto const PlayerSate = GetPlayerState<ATLVPlayerState>();
	check(PlayerSate)

	if (auto const TLVPlayerController = Cast<ATLVPlayerController>(GetController()))
	{
		if (auto const TLVHUD = Cast<ATLVHUD>(TLVPlayerController->GetHUD()))
		{
			TLVHUD->InitOverlay(TLVPlayerController, PlayerSate, AbilitySystemComponent, AttributeSet);
			
		}
	}
	if (!HasAuthority()) return;

	AbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}

void ATLVCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FRotator MovementRotation(0.f,Controller->GetControlRotation().Yaw,0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(ForwardDirection,MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(RightDirection,MovementVector.X);
	}
}

void ATLVCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATLVCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void ATLVCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? TLVGameplayTags::Player_Event_SwitchTarget_Right : TLVGameplayTags::Player_Event_SwitchTarget_Left,
		Data
	);
	GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Green, SwitchDirection.ToString());

}

void ATLVCharacter::Input_AbilityInputPressed(FGameplayTag InputTag)
{
	auto const TLVASC = Cast<UTLVAbilitySystemComponent>(AbilitySystemComponent);
	TLVASC->OnAbilityInputPressed(InputTag);

}

void ATLVCharacter::Input_AbilityInputReleased(FGameplayTag InputTag)
{
	auto const TLVASC = Cast<UTLVAbilitySystemComponent>(AbilitySystemComponent);
	TLVASC->OnAbilityInputReleased(InputTag);

}
