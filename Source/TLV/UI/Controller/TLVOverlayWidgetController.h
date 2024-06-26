﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVUserWidgetController.h"
#include "TLVOverlayWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealtChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealtChangedSignature, float, NewMaxHealth);
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TLV_API UTLVOverlayWidgetController : public UTLVUserWidgetController
{
	GENERATED_BODY()
public:

    virtual void BroadcastInitialValues() override;
    virtual void BindCallbacksToDependencies() override;

    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnHealtChangedSignature OnHealthChanged;
	
    UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
    FOnHealtChangedSignature OnMaxHealthChanged;
    
protected:

	void HealthChanged(FOnAttributeChangeData const& data) const;
	void MaxHealthChanged(FOnAttributeChangeData const& data) const;
};
