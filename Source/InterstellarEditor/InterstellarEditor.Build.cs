// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;

public class InterstellarEditor : ModuleRules
{
	public InterstellarEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        bEnforceIWYU = true;

        PublicIncludePaths.AddRange(
            new string[] { "InterstellarEditor/Public" });

        PrivateIncludePaths.AddRange(
            new string[] { "InterstellarEditor/Private" });

        PublicDependencyModuleNames.AddRange(
            new string[] { "Core"
                         , "CoreUObject"
                         , "Engine"
                         , "EngineSettings"
                         , "InputCore"
                         , "RenderCore"
                         , "Renderer"
                         , "RHI"
                         , "ShaderCore"
                         , "OnlineSubsystem"
                         , "OnlineSubsystemUtils"
                         , "UMG" });

		PrivateDependencyModuleNames.AddRange(
            new string[] { "Interstellar"
                         , "Slate"
                         , "SlateCore"
                         , "OnlineSubsystem"
                         , "UnrealEd" });
    }
}
