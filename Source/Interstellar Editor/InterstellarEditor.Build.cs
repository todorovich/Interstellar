// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;

public class InterstellarEditor : ModuleRules
{
	public InterstellarEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] 
            { "Interstellar/Public"
            , "Interstellar Editor/Public"
            });

        PrivateIncludePaths.AddRange(
            new string[]
            { "Interstellar/Private"
            , "Interstellar Editor/Private"
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
