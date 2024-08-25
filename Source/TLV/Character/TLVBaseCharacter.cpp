// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBaseCharacter.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/Player/TLVPlayerState.h"

// Sets default values
ATLVBaseCharacter::ATLVBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

UAbilitySystemComponent* ATLVBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATLVBaseCharacter::TryActivateGameplayAbility()
{
	Cast<UTLVAbilitySystemComponent>(AbilitySystemComponent)->TryActivateGameplayAbility();

}

USkeletalMeshComponent* ATLVBaseCharacter::GetVisibleMesh() const
{
	return RetargetedMesh != nullptr ? RetargetedMesh.Get() : GetMesh(); 
}

// Called when the game starts or when spawned
void ATLVBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATLVBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ensureMsgf(!StartUpData.IsNull(), TEXT("Assign startup data to %s"), *GetName());
}

void ATLVBaseCharacter::AddCharacterAbilities()
{
	if (!HasAuthority()) return;

	auto const TLVASC = CastChecked<UTLVAbilitySystemComponent>(AbilitySystemComponent);
	TLVASC->AddCharacterAbilities(StartupAbilities);
}

void ATLVBaseCharacter::InitAbilityComponent()
{
	auto* MyPlayerState = GetPlayerState<ATLVPlayerState>();
	check(MyPlayerState);
	MyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(MyPlayerState, this);
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();

	if (!HasAuthority()) return;
	auto const TLVASC = CastChecked<UTLVAbilitySystemComponent>(AbilitySystemComponent);
	TLVASC->AddCharacterAbilities(StartupAbilities);

}



