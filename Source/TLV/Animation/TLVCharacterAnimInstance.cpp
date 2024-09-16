// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCharacterAnimInstance.h"

#include "TLV/Character/TLVCharacter.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTLVCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
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
		GEngine->AddOnScreenDebugMessage(1233, 4, FColor::Orange, Character->GetVelocity().ToString());
	}
}

void UTLVCharacterAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ATLVBaseCharacter>(TryGetPawnOwner());
	if (Character)
	{
		OwningMovementComponent = Character->GetCharacterMovement();
	}
}

void UTLVCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningMovementComponent) return;
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D()>0.f;
	GroundSpeed = Character->GetVelocity().Size2D();
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(Character->GetVelocity(),Character->GetActorRotation());
}

// Weapon needs a socket called "LeftHandSocket"
void UTLVCharacterAnimInstance::CalculateTransformationToAttachLeftHandToWeapon()
{
	if (!Character->Weapon) return;
	
	LeftHandTransform = Character->Weapon->GetSocketTransform(FName("LeftHandSocket"), ERelativeTransformSpace::RTS_World);
	FVector OutPosition;
	FRotator OutRotation;
	Character->GetVisibleMesh()->TransformToBoneSpace(FName("hand_r"), LeftHandTransform.GetLocation(), LeftHandTransform.GetRotation().Rotator(), OutPosition, OutRotation);
	LeftHandTransform.SetLocation(OutPosition);
	LeftHandTransform.SetRotation(OutRotation.Quaternion());
}

void UTLVCharacterAnimInstance::UpdateProjectileWeaponAttributes()
{
}