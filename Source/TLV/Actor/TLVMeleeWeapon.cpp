// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVMeleeWeapon.h"


// Sets default values
ATLVMeleeWeapon::ATLVMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox =CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void ATLVMeleeWeapon::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	auto const Pawn = GetInstigator<APawn>();
	checkf(Pawn, TEXT("Weapon has no instigator"))
	if (auto const HitPawn = Cast<APawn>(OtherActor))
	{
		if (Pawn != HitPawn)
		{
			OnHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void ATLVMeleeWeapon::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto const Pawn = GetInstigator<APawn>();
	checkf(Pawn, TEXT("Weapon has no instigator"))
	if (auto const HitPawn = Cast<APawn>(OtherActor))
	{
		if (Pawn != HitPawn)
		{
			OnPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}



