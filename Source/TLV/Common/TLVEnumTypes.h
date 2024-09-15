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