// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class ETLVConfirmType : uint8
{
	YES,
	NO
};

UENUM()
enum class ETLVValidType : uint8
{
	VALID,
	INVALID
};


UENUM()
enum class ETLVSuccessType : uint8
{
	Success,
	Failed
};

UENUM()
enum class ETLVWeaponType : uint8
{
	Weapon,
	Hand
};

UENUM()
enum class ETLVGraphicSettings: uint8
{
	Shadow,
	Shading,
	Texture,
	GlobalIllumination,
	Foliage,
	ViewDistance,
	VFX
};