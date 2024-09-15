// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TLV/Common/TLVStructTypes.h"
#include "TLVMeleeWeapon.generated.h"
DECLARE_DELEGATE_OneParam(FOnTargetInteractedDelegate, AActor*)
UCLASS()
class TLV_API ATLVMeleeWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATLVMeleeWeapon();
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual  void OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapons")
	FTLVHeroWeaponData HeroWeaponData;
	UFUNCTION(BlueprintCallable)
	void AssignGrantedAbilitySpecHandles(TArray<FGameplayAbilitySpecHandle> const& AbilitySpecHandles);
	UFUNCTION(BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetGrantedAbilitySpecHandles() const;
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() { return WeaponCollisionBox;}
private:
	TArray<FGameplayAbilitySpecHandle> GrantedAbilitySpecHandles;
};
