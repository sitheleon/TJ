// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class A_TongJeon : ModuleRules
{
	public A_TongJeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "GameplayTasks" });
	}
}
