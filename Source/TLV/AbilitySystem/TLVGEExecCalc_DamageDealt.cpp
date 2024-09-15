// Fill out your copyright notice in the Description page of Project Settings.


#include "TLVGEExecCalc_DamageDealt.h"

#include <string>

#include "TLVAttributeSet.h"
#include "TLV/Assets/TLVGameplayTags.h"

struct FTLVDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FTLVDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTLVAttributeSet,AttackPower,Source,false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTLVAttributeSet,DefensePower,Target,false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTLVAttributeSet,DamageTaken,Target,false)	}
};

static const FTLVDamageCapture& GetTLVDamageCapture()
{
	static FTLVDamageCapture DamageCapture;
	return DamageCapture;
}
UTLVGEExecCalc_DamageDealt::UTLVGEExecCalc_DamageDealt()
{
	/*
	auto const HealthPropery = FindFieldChecked<FProperty>(UTLVAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UTLVAttributeSet, Health));
	FGameplayEffectAttributeCaptureDefinition GameplayEffectAttributeCaptureDefinition(
		HealthPropery,
		EGameplayEffectAttributeCaptureSource::Source,
		false
		);
	RelevantAttributesToCapture.Add(GameplayEffectAttributeCaptureDefinition);
	*/

	RelevantAttributesToCapture.Add(GetTLVDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetTLVDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetTLVDamageCapture().DamageTakenDef);}

void UTLVGEExecCalc_DamageDealt::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = ExecutionParams.GetOwningSpec().CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = ExecutionParams.GetOwningSpec().CapturedTargetTags.GetAggregatedTags();
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetTLVDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);
	GEngine->AddOnScreenDebugMessage(1, 4, FColor::Emerald, FString(std::to_string(SourceAttackPower).c_str()));

	float BaseDamage = 0.f;
	int32 UsedLightAttckComboCount = 0;
	int32 UsedHeavyAttackComboCount = 0;
	
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(TLVGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(TLVGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsedLightAttckComboCount = TagMagnitude.Value;
		}

		if (TagMagnitude.Key.MatchesTagExact(TLVGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsedHeavyAttackComboCount = TagMagnitude.Value;
		}
	}

	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetTLVDamageCapture().DefensePowerDef,EvaluateParameters,TargetDefensePower);
	GEngine->AddOnScreenDebugMessage(2, 4, FColor::Emerald, FString(std::to_string(TargetDefensePower).c_str()));
	/*Debug::Print(TEXT("TargetDefensePower"),TargetDefensePower);*/

	if (UsedLightAttckComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsedLightAttckComboCount - 1) * 0.05f + 1.f;

		BaseDamage *= DamageIncreasePercentLight;
		GEngine->AddOnScreenDebugMessage(3, 4, FColor::Emerald, FString(std::to_string(BaseDamage).c_str()));
		/*Debug::Print(TEXT("ScaledBaseDamageLight"),BaseDamage);*/
	}

	if (UsedHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;

		BaseDamage *= DamageIncreasePercentHeavy;
		GEngine->AddOnScreenDebugMessage(4, 4, FColor::Emerald, FString(std::to_string(BaseDamage).c_str()));

		/*Debug::Print(TEXT("ScaledBaseDamageHeavy"),BaseDamage);*/
	}

	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	GEngine->AddOnScreenDebugMessage(5, 4, FColor::Emerald, FString(std::to_string(FinalDamageDone).c_str()));
	/*Debug::Print(TEXT("FinalDamageDone"),FinalDamageDone);*/

	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetTLVDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
