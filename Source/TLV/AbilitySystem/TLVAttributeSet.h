// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TLVAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> SourceController = nullptr;;
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;
	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor = nullptr;
	UPROPERTY()
	TObjectPtr<AController> TargetController = nullptr;
	FGameplayEffectContextHandle GameplayEffectContextHandle = {};
};
/**
 * 
 */
UCLASS()
class TLV_API UTLVAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTLVAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "TLV | Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "TLV | Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "TLV | Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "TLV | Vital Attributes")
	FGameplayAttributeData MaxStamina;;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, Category = "TLV | Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet,AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "TLV | Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet,DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "TLV | Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UTLVAttributeSet,DamageTaken)
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& EffectProperties);
};
