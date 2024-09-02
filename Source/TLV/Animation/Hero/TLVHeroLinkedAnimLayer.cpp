// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVHeroLinkedAnimLayer.h"

UTLVHeroAnimInstance* UTLVHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UTLVHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
