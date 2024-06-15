// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVUserWidgetController.h"

void UTLVUserWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UTLVUserWidgetController::BroadcastInitialValues()
{
}

void UTLVUserWidgetController::BindCallbacksToDependencies()
{
}
