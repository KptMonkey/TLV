// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVAnimInstance.h"

#include "TLV/Character/TLVCharacter.h"

void UTLVAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (!Character) return;

	CalculateTransformationToAttachLeftHandToWeapon();
	UpdateProjectileWeaponAttributes();
	if (Character->Weapon)
	{
		// Draw Debug Line
		const FVector SocketLocation = Character->Weapon->GetSocketLocation("SpawnProjectile");
		auto const SocketRotation = Character->Weapon->GetSocketRotation("SpawnProjectile");
		auto const Direction = SocketRotation.Quaternion().GetRightVector();
		DrawDebugLine(GetWorld(), SocketLocation, SocketLocation + Direction * 10000, FColor::Green);
	}
}

void UTLVAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ATLVCharacter>(TryGetPawnOwner());
}

void UTLVAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

// Weapon needs a socket called "LeftHandSocket"
void UTLVAnimInstance::CalculateTransformationToAttachLeftHandToWeapon()
{
	if (!Character->Weapon) return;
	
	LeftHandTransform = Character->Weapon->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
	FVector OutPosition;
	FRotator OutRotation;
	Character->GetVisibleMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), LeftHandTransform.GetRotation().Rotator(), OutPosition, OutRotation);
	LeftHandTransform.SetLocation(OutPosition);
	LeftHandTransform.SetRotation(OutRotation.Quaternion());
}

void UTLVAnimInstance::UpdateProjectileWeaponAttributes()
{
	if (!Character->ProjectileWeapon) return;
	AimOffset = Character->ProjectileWeapon->AimOffset;
}

