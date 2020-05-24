namespace UnrealBuildTool.Rules
{
	public class LerpBar : ModuleRules
	{
		public LerpBar(ReadOnlyTargetRules Target) : base(Target)
		{
// 			PublicIncludePaths.AddRange(
// 				new string[] {
// 					// ... add public include paths required here ...
// 				}
// 				);
// 
// 			PrivateIncludePaths.AddRange(
// 				new string[] {
// 					// ... add other private include paths required here ...
// 				}
// 				);
// 
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"UMG",
					"SlateCore"
				}
				);
// 
// 			PrivateDependencyModuleNames.AddRange(
// 				new string[]
// 				{
// 					// ... add private dependencies that you statically link with here ...
// 				}
// 				);
// 
// 			DynamicallyLoadedModuleNames.AddRange(
// 				new string[]
// 				{
// 					// ... add any modules that your module loads dynamically here ...
// 				}
// 				);
		}
	}
}
