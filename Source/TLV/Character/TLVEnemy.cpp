// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVEnemy.h"

#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/AbilitySystem/TLVAttributeSet.h"


// Sets default values
ATLVEnemy::ATLVEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	AbilitySystemComponent = CreateDefaultSubobject<UTLVAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UTLVAttributeSet>("AttributeSet");
}

void ATLVEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}


