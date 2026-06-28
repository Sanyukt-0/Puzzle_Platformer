// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PuzzlePlatformer : ModuleRules
{
	public PuzzlePlatformer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PuzzlePlatformer",
			"PuzzlePlatformer/Variant_Platforming",
			"PuzzlePlatformer/Variant_Platforming/Animation",
			"PuzzlePlatformer/Variant_Combat",
			"PuzzlePlatformer/Variant_Combat/AI",
			"PuzzlePlatformer/Variant_Combat/Animation",
			"PuzzlePlatformer/Variant_Combat/Gameplay",
			"PuzzlePlatformer/Variant_Combat/Interfaces",
			"PuzzlePlatformer/Variant_Combat/UI",
			"PuzzlePlatformer/Variant_SideScrolling",
			"PuzzlePlatformer/Variant_SideScrolling/AI",
			"PuzzlePlatformer/Variant_SideScrolling/Gameplay",
			"PuzzlePlatformer/Variant_SideScrolling/Interfaces",
			"PuzzlePlatformer/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
