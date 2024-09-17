// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVMeleeHand.h"

#include "Components/BoxComponent.h"
#include "TLV/BlueprintFunctionLibrary/TLVBlueprintFunctionLibrary.h"


// Sets default values
ATLVMeleeHand::ATLVMeleeHand()
{
	PrimaryActorTick.bCanEverTick = false;

	HandCollisionBox =CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	SetRootComponent(HandCollisionBox);
	HandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxBeginOverlap);
	HandCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnCollisionBoxEndOverlap);
}

void ATLVMeleeHand::ToggleCollision(bool bEnable)
{
	auto const CollisionEnabled = bEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision;
	HandCollisionBox->SetCollisionEnabled(CollisionEnabled);
}

void ATLVMeleeHand::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto const Pawn = GetInstigator<APawn>();
	checkf(Pawn, TEXT("Weapon has no instigator"))
	if (auto const HitPawn = Cast<APawn>(OtherActor))
	{
		if (UTLVBlueprintFunctionLibrary::IsTargetPawnHostile(Pawn, HitPawn))
		{
			OnHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}

void ATLVMeleeHand::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto const Pawn = GetInstigator<APawn>();
	checkf(Pawn, TEXT("Weapon has no instigator"))
	if (auto const HitPawn = Cast<APawn>(OtherActor))
	{
		if (UTLVBlueprintFunctionLibrary::IsTargetPawnHostile(Pawn, HitPawn))
		{
			OnPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}



