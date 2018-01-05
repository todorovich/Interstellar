// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;

public class InterstellarEditor : ModuleRules
{
	public InterstellarEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //PublicIncludePaths.AddRange(
        //    new string[] { "InterstellarEditor/Public" });

        //PrivateIncludePaths.AddRange(
        //    new string[] { "InterstellarEditor/Private" });

        PublicDependencyModuleNames.AddRange(
            new string[] { "UnrealEd" });

		PrivateDependencyModuleNames.AddRange(
            new string[] { "Slate"
                         , "SlateCore"
                         , "OnlineSubsystem"
                         , "UnrealEd" });
    }
}
