// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TLVBaseComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TLV_API UTLVBaseComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	template <class T>
	TObjectPtr<T> GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "Must derive from APawn");
		return CastChecked<T>(GetOwner());
	}

	TObjectPtr<APawn> GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	TObjectPtr<T> GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "Must derive from AController");
		return GetOwningPawn<APawn>()->GetController<T>();		
	}
};
