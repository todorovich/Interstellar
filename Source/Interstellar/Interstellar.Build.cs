// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;

public class Interstellar : ModuleRules
{
	public Interstellar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnforceIWYU = true;

		PublicIncludePaths.AddRange(
			new string[] 
            { "Interstellar/Public" });

		PrivateIncludePaths.AddRange(
			new string[] 
            { "Interstellar/Private" });

		PublicDependencyModuleNames.AddRange(
			new string[] 
            { "Core"
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
			, "UMG"
            //, "UnrealEd"
            });

		PrivateDependencyModuleNames.AddRange(
			new string[] 
            { "Slate"
			, "SlateCore"
			, "OnlineSubsystem"
            });


        //PrivateIncludePathModuleNames.AddRange(
        //    new string[]
        //    {
        //        "Interstellar"
        //    });

        //DynamicallyLoadedModuleNames.AddRange(
        //    new string[]
        //    {
        //    });
    }
}
