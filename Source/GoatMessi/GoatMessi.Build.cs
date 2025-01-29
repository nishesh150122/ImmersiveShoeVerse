// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GoatMessi : ModuleRules
{
	public GoatMessi(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"DatabaseSupport",
			"SQLiteCore",
			"SQLiteSupport"
			
		});
	}
}
