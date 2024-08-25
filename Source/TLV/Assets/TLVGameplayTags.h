#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

struct FTLVGameplayTags
{
	static const FTLVGameplayTags& Get() { return GameplayTags;}
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Health;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag Shoot;
	FGameplayTag Reload;
	FGameplayTag Damage;
	FGameplayTag Effects_HitReact;
private:
	static FTLVGameplayTags GameplayTags;
};

namespace TLVGameplayTags
{
	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe)

	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)	
	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)	
	TLV_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)	
}