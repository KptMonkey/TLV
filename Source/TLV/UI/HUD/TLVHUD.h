// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TLVHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UTLVOverlayWidgetController;
class UTLVUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class TLV_API ATLVHUD : public AHUD
{
	GENERATED_BODY()
public:

	UPROPERTY()
	TObjectPtr<UTLVUserWidget>  OverlayWidget;

	UTLVOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTLVUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UTLVOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTLVOverlayWidgetController> OverlayWidgetControllerClass;
};
