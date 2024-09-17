// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBaseCharacter.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ATLVBaseCharacter::ATLVBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UTLVAbilitySystemComponent>("TLVAbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UTLVAttributeSet>("TLVAttributeSet");
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
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
	return VisibleMesh != nullptr ? VisibleMesh.Get() : GetMesh(); 
}

USkeletalMeshComponent* ATLVBaseCharacter::GetAnimatedMesh() const
{
	return  AnimatedMesh != nullptr ? AnimatedMesh.Get() : GetMesh(); 
}

TObjectPtr<UTLVCombatComponent> ATLVBaseCharacter::GetCombatComponent() const
{
	return nullptr;
}

// Called when the game starts or when spawned
void ATLVBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATLVBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		ensureMsgf(!StartUpData.IsNull(), TEXT("Assign startup data to %s"), *GetName());
	}
}

void ATLVBaseCharacter::AddCharacterAbilities() const
{
	if (!HasAuthority()) return;

	AbilitySystemComponent->AddCharacterAbilities(StartupAbilities);
}





