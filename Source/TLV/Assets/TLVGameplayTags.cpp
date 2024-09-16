#include "TLVGameplayTags.h"
#include "GameplayTagsManager.h"

FTLVGameplayTags FTLVGameplayTags::GameplayTags;

void FTLVGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	GameplayTags.Attributes_Primary_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Health"),
		FString("The Health")
		);
	

	/*
	 * Input Tags
	 */
	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
		);

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
		);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effects.HitReact"),
	FString("Tag granted when Hit Reacting")
	);
}

namespace TLVGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_EquipAxe, "InputTag.EquipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UnequipAxe, "InputTag.UnequipAxe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack_Axe, "InputTag.LightAttack.Axe")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack_Axe, "InputTag.HeavyAttack.Axe")
	
	
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Equip_Axe, "Player.Event.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Unequip_Axe, "Player.Event.Unequip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Hit_Pause, "Player.Event.Hit.Pause")

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Axe, "Player.Ability.Equip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Axe, "Player.Ability.Unequip.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Melee_Light_Axe, "Player.Ability.Attack.Melee.Light.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Melee_Heavy_Axe, "Player.Ability.Attack.Melee.Heavy.Axe")
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Hit_Pause, "Player.Ability.Hit.Pause")

	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Axe, "Player.Weapon.Axe")

	UE_DEFINE_GAMEPLAY_TAG(Player_Status_JumpToFinisher, "Player.Status.JumpToFinisher")

	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light")
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_Melee_Hit, "Shared.Event.Melee.Hit")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Front_Head, "Shared.Event.HitReact.Light.Front.Head")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Front_Torso, "Shared.Event.HitReact.Light.Front.Torso")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Left_Head_Up, "Shared.Event.HitReact.Light.Left.Head.Up")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Left_Head_Down, "Shared.Event.HitReact.Light.Left.Head.Down")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Left_Torso, "Shared.Event.HitReact.Light.Left.Torso")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Right_Head_Down, "Shared.Event.HitReact.Light.Right.Head.Down")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Right_Head_Up, "Shared.Event.HitReact.Light.Right.Head.Up")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Light_Right_Torso, "Shared.Event.HitReact.Light.Right.Torso")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Front_Head, "Shared.Event.HitReact.Heavy.Front.Head")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Front_Torso, "Shared.Event.HitReact.Heavy.Front.Torso")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Left_Head_Up, "Shared.Event.HitReact.Heavy.Left.Head.Up")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Left_Head_Down, "Shared.Event.HitReact.Heavy.Left.Head.Down")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Left_Torso, "Shared.Event.HitReact.Heavy.Left.Torso")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Right_Head_Down, "Shared.Event.HitReact.Heavy.Right.Head.Down")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Right_Head_Up, "Shared.Event.HitReact.Heavy.Right.Head.Up")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact_Heavy_Right_Torso, "Shared.Event.HitReact.Heavy.Right.Torso")

	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage")


	
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee, "Enemy.Ability.Melee")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death")

	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Death, "Shared.Status.Death")

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing")
}
