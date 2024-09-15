// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCharacter.h"

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

ATLVCharacter::ATLVCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	HeroCombatComponent = CreateDefaultSubobject<UTLVHeroCombatComponent>("CombatComponent");
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
		TraceUnderCrosshair(TraceHitResult);
		OnRep_DefendsBiteAttempt();
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
