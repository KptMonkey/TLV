// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TLV : ModuleRules
{
	public TLV(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayAbilities", "AIModule", "UMG", "MotionWarping",  "MoviePlayer"  });

		PrivateDependencyModuleNames.AddRange(new string[] {  "GameplayTags", "GameplayTasks", "NavigationSystem", "Niagara", "AnimGraphRuntime", "AnimGraphRuntime", "AIModule", "UMG", "MoviePlayer" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
