// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVCrosshairWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Kismet/KismetMathLibrary.h"
#include "TLV/Character/TLVCharacter.h"

void UTLVCrosshairWidget::UpdateCrosshairPosition()
{
	auto const PlayerCharacter = Cast<ATLVCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter == nullptr) return;
	
	auto Velocity = PlayerCharacter->GetVelocity();
	Velocity.Normalize();
	auto const VelocityScale = Velocity.Length();

	auto CHT = CrosshairTopPos;
	auto CHB = CrosshairBottomPos;
	auto CHR = CrosshairRightPos;
	auto CHL = CrosshairLeftPos;
	
	ClampCrosshairPosition(VelocityScale, GunAimingSpread, CHT, CHB, CHL, CHR);
	
	CrosshairTop->SetPosition(CHT);
	CrosshairBottom->SetPosition(CHB);
	CrosshairRight->SetPosition(CHR);
	CrosshairLeft->SetPosition(CHL);
}

void UTLVCrosshairWidget::SetCrosshairs(UWidget* CrosshairTopIn, UWidget* CrosshairBottomIn, UWidget* CrosshairLeftIn,
	UWidget* CrosshairRightIn)
{
	auto const PlayerCharacter = Cast<ATLVCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter == nullptr) return;
	
	CrosshairTop = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairTopIn);
	CrosshairBottom = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairBottomIn);
	CrosshairLeft = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairLeftIn);
	CrosshairRight = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrosshairRightIn);
	
	CrosshairTopPos = CrosshairTop->GetPosition();
	CrosshairBottomPos = CrosshairBottom->GetPosition();
	CrosshairLeftPos = CrosshairLeft->GetPosition();
	CrosshairRightPos = CrosshairRight->GetPosition();

	CalculateCrosshairCenterPosition();
	PlayerCharacter->CrosshairWidget = this;
}

void UTLVCrosshairWidget::SetHitCrosshairs(UWidget* CrosshairTopIn, UWidget* CrosshairBottomIn, UWidget* CrosshairLeftIn,
	UWidget* CrosshairRightIn)
{
	HitCrosshairs[0] = CrosshairTopIn;
	HitCrosshairs[1] = CrosshairBottomIn;
	HitCrosshairs[2] = CrosshairLeftIn;
	HitCrosshairs[3] = CrosshairRightIn;
	HideHitCrosshair();
}

void UTLVCrosshairWidget::HideHitCrosshair()
{
	for (auto HitCrosshair : HitCrosshairs)
	{
		HitCrosshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UTLVCrosshairWidget::DisplayHitCrosshair()
{
	for (auto HitCrosshair : HitCrosshairs)
	{
		HitCrosshair->SetVisibility(ESlateVisibility::Visible);
	}
	GetWorld()->GetTimerManager().SetTimer(HitCrosshairTimer, this, &ThisClass::HideHitCrosshair, 0.12f, false);
}

void UTLVCrosshairWidget::ClampCrosshairPosition(float val, float spread, FVector2D& CHT, FVector2D& CHB, FVector2D& CHL,
	FVector2D& CHR)
{
	CHT.Y = UKismetMathLibrary::MapRangeClamped(val, 0.0, 1.0, CrosshairTopPos.Y, CrosshairTopPos.Y - spread);
	CHB.Y = UKismetMathLibrary::MapRangeClamped(val, 0.0, 1.0, CrosshairBottomPos.Y, CrosshairBottomPos.Y + spread);
	CHL.X = UKismetMathLibrary::MapRangeClamped(val, 0.0, 1.0, CrosshairLeftPos.X, CrosshairLeftPos.X - spread);
	CHR.X = UKismetMathLibrary::MapRangeClamped(val, 0.0, 1.0, CrosshairRightPos.X, CrosshairRightPos.X + spread);
}

void UTLVCrosshairWidget::CalculateCrosshairCenterPosition()
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D const ScreenCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);

	CrosshairCenter.X = ScreenCenter.X;
	CrosshairCenter.Y = ScreenCenter.Y;
	CrosshairCenter = ScreenCenter;
}
