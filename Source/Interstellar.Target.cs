// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class InterstellarTarget : TargetRules
{
	public InterstellarTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Interstellar" } );

        if (bBuildEditor)
        {
           ExtraModuleNames.Add("InterstellarEditor");
        }
    }
}
