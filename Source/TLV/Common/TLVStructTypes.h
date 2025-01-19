#pragma once
#include "TLV/Animation/Hero/TLVHeroLinkedAnimLayer.h"
#include "TLV/AbilitySystem/Ability/TLVGameplayAbility.h"
#include "TLVStructTypes.generated.h"

class UInputMappingContext;

USTRUCT(BlueprintType)
struct FTLVHeroAbilitySet
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "TLV | InputTag"))
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "TLV | Input"))
	TArray<FTLVHeroAbilitySet> DefaultWeaponAbilities;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "TLV | Input"))
	UInputMappingContext* WeaponInputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage;
};

USTRUCT(BlueprintType)
struct FTLVGameplayMontage
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "TLV | Animation"))
	UAnimMontage* AnimMontage = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "TLV | Animation"))
	FGameplayTag GameplayTag;
};

USTRUCT(BlueprintType)
struct FTLVGraphicSettings
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int AntiAliasing = 2;
	UPROPERTY(BlueprintReadWrite)
	int ShadowQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ShadingQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int TextureQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ViewDistanceQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int VFXQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int FoliageQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int GIQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int ReflectionQuality = 2;
	UPROPERTY(BlueprintReadWrite)
	int FullScreen = 0;
};