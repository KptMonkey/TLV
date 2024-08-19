// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVProjectileWeapon.h"


// Sets default values
ATLVProjectileWeapon::ATLVProjectileWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	SetRootComponent(SkeletalMeshComponent);
	
	SkeletalMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


