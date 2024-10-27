// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLV/AbilitySystem/Ability/TLVHeroGameplayAbility.h"
#include "TLVHeroGameplayAbilityTargetLock.generated.h"

/**
 * 
 */
UCLASS()
class TLV_API UTLVHeroGameplayAbilityTargetLock : public UTLVHeroGameplayAbility
{
	GENERATED_BODY()
protected:
	void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(FGameplayTag const& SwitchDirectionTag);
	UFUNCTION(BlueprintPure)
	FVector CalculateWarpTargetLocation(bool& IsValid);
	UFUNCTION(BlueprintPure)
	bool IsInMotionWarpingDistance();
private:
	void TryLockOnTarget();
	void GetAvailableActorsToLock();
	TObjectPtr<AActor> GetNearestTargetFromAvailableActors(const TArray<TObjectPtr<AActor>>& InAvailableActors);
	void CancelTargetLockAbility();
	void CleanUp();
	void ResetTargetLockMappingContext();
	void InitTargetLockMappingContext();
	void GetAvailableActorsAroundTarget(TArray<TObjectPtr<AActor>>& ActorsOnLeft, TArray<TObjectPtr<AActor>>& ActorsOnRight);
	
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	FVector TraceBoxSize = FVector(5000.f,5000.f,300.f);

	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	TArray< TEnumAsByte < EObjectTypeQuery > > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	bool bShowPersistentDebugShape = false;
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;
	UPROPERTY()
	TArray<TObjectPtr<AActor>> AvailableActorsToLock;
	UPROPERTY()
	TObjectPtr<AActor> CurrentLockedActor;
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	UInputMappingContext* TargetLockMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Target Lock")
	float TargetOffsetDistance = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Motion Warping")
	float WarpTargetLocationOffset = 180.f;
	UPROPERTY(EditDefaultsOnly, Category = "TLV | Motion Warping")
	float MotionWarpingDistance = 700.f;
};