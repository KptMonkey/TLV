#pragma once
#include "TLV/Animation/Hero/TLVHeroLinkedAnimLayer.h"
#include "TLV/AbilitySystem/Ability/TLVGameplayAbility.h"
#include "TLVStructTypes.generated.h"

class UInputMappingContext;

USTRUCT(BlueprintType)
struct FTLVHeroAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UTLVGameplayAbility> AbilityToGrant;
	bool IsValid() const;

};

USTRUCT(BlueprintType)
struct FTLVHeroWeaponData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UTLVHeroLinkedAnimLayer> WeaponAnimLayerToLink;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	TArray<FTLVHeroAbilitySet> DefaultWeaponAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	UInputMappingContext* WeaponInputMappingContext;
};
