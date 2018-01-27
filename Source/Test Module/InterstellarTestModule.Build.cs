// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;

public class InterstellarTestModule : ModuleRules
{
	public InterstellarTestModule(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[]
            { "Test Module/Private"
            });

        PublicIncludePaths.AddRange(
            new string[]
            { "Test Module/Public"
            });

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
            , "UnrealEd"
            });

		PrivateDependencyModuleNames.AddRange(
            new string[] 
            { "Slate"  
            , "SlateCore"
            , "OnlineSubsystem"
            });
    }
}
