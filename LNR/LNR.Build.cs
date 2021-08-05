// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LNR : ModuleRules
{
	public LNR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "GameplayAbilities", "GameplayTags", "GameplayTasks", "UMG", "OnlineSubsystemUtils", "DeveloperSettings" });
		
		PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "Http", "Json" });
	}
}
