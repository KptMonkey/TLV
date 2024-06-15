// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVUserWidget.h"

void UTLVUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
