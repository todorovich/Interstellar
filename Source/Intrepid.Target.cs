// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntrepidTarget : TargetRules
{
	public IntrepidTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Intrepid" } );
	}
}
