// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLVUserWidget.h"
#include "TLVCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVCrosshairWidget : public UTLVUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void UpdateCrosshairPosition();

	UFUNCTION(BlueprintCallable)
	void SetCrosshairs(UWidget* CrosshairTopIn,
		UWidget* CrosshairBottomIn,
		UWidget* CrosshairLeftIn,
		UWidget* CrosshairRightIn);

	UFUNCTION(BlueprintCallable)
	void SetHitCrosshairs(UWidget* CrosshairTopIn,
		UWidget* CrosshairBottomIn,
		UWidget* CrosshairLeftIn,
		UWidget* CrosshairRightIn);
	
	void HideHitCrosshair();
	void DisplayHitCrosshair();
	
	FTimerHandle HitCrosshairTimer;
	UPROPERTY(EditAnywhere)
	float GunAimingSpread = 16.f;
	UPROPERTY(EditAnywhere)
	float HitCrosshairFadeTime = 0.12;
private:
	void ClampCrosshairPosition(float val, float spread, FVector2D& CHT, FVector2D& CHB,FVector2D& CHL,FVector2D& CHR);
	void CalculateCrosshairCenterPosition();
	UPROPERTY()
	TObjectPtr<class UCanvasPanelSlot> CrosshairTop = nullptr;
	UPROPERTY()
	TObjectPtr<UCanvasPanelSlot> CrosshairBottom = nullptr;
	UPROPERTY()
	TObjectPtr<UCanvasPanelSlot> CrosshairRight = nullptr;
	UPROPERTY()
	TObjectPtr<UCanvasPanelSlot> CrosshairLeft = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UWidget>> HitCrosshairs{nullptr, nullptr, nullptr, nullptr};
	
	FVector2D CrosshairTopPos = {0.f, 0.f};
	FVector2D CrosshairBottomPos = {0.f, 0.f};
	FVector2D CrosshairRightPos = {0.f, 0.f};
	FVector2D CrosshairLeftPos = {0.f, 0.f};
public:
	UPROPERTY()
	FVector2D CrosshairCenter = {0.f, 0.f};
};
