// Copyright 2017 Micho Todorovich, all rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class IntrepidEditorTarget : TargetRules
{
	public IntrepidEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Intrepid" } );
	}
}
