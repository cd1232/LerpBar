using UnrealBuildTool;
using System.Collections.Generic;

public class LerpBarProjectEditorTarget : TargetRules
{
	public LerpBarProjectEditorTarget (TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.Add("LerpBarProject");
	}
}
