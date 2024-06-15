// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVBaseCharacter.h"

// Sets default values
ATLVBaseCharacter::ATLVBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ATLVBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ATLVBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



