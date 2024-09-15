// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Character.h"
#include "TLV/Component/Combat/TLVCombatInterface.h"
#include "TLV/UI/TLVCrosshairWidget.h"
#include "TLVBaseCharacter.generated.h"

class UTLVAttributeSet;
class UTLVAbilitySystemComponent;
class UAttributeSet;
class UTLVDataAssetStartupData;
UCLASS()
class TLV_API ATLVBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ITLVCombatInterface
{
	GENERATED_BODY()

public:
	ATLVBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable)
	void TryActivateGameplayAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY()
	TObjectPtr<UTLVCrosshairWidget> CrosshairWidget;
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetVisibleMesh() const;
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetAnimatedMesh() const;
	FORCEINLINE TObjectPtr<UTLVAttributeSet> GetTLVAttributeSet() const { return AttributeSet;}
	virtual TObjectPtr<UTLVCombatComponent> GetCombatComponent() const override;
protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	void AddCharacterAbilities() const;
	

	UPROPERTY()
	TObjectPtr<UTLVAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TLV | Abilities")
	TObjectPtr<UTLVAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TLV | Data")
	TSoftObjectPtr<UTLVDataAssetStartupData> StartUpData;
	UPROPERTY(EditAnywhere, Category="TLV | Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TLV | Retargeted Mesh")
	TObjectPtr<USkeletalMeshComponent> VisibleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TLV | Animated Mesh")
	TObjectPtr<USkeletalMeshComponent> AnimatedMesh;
};
