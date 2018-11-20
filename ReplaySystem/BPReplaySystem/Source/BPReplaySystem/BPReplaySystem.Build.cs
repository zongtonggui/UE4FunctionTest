// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class BPReplaySystem : ModuleRules
{
	public BPReplaySystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Json", "NetworkReplayStreaming" });

        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystemNull" });

    }
}
