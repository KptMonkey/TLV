// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "TLV/AbilitySystem/TLVAbilitySystemComponent.h"
#include "TLV/Input/TLVInputConfig.h"
#include "TLVPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class TLV_API ATLVPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ATLVPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	virtual FGenericTeamId GetGenericTeamId() const override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	FGenericTeamId TeamId = 0;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> TLVContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void ABilityInputTagHeld(FGameplayTag InputTag);
	void Move(const FInputActionValue& InputActionValue);
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UTLVInputConfig> InputConfig;
	UPROPERTY()
	TObjectPtr<UTLVAbilitySystemComponent> TLVAbilitySystemComponent;
	TObjectPtr<UTLVAbilitySystemComponent> GetASC();
};
