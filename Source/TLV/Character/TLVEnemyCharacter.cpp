// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemyCharacter.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"


// Sets default values
ATLVEnemyCharacter::ATLVEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UTLVAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UTLVAttributeSet>("AttributeSet");
}

void ATLVEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityComponent();
}

void ATLVEnemyCharacter::InitAbilityComponent()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UTLVAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}


