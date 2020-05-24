using UnrealBuildTool;
using System.Collections.Generic;

public class LerpBarProjectTarget : TargetRules
{
	public LerpBarProjectTarget (TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("LerpBarProject");
	}
}
