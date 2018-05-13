// M3 Android Functions
// (c) 2018 Mark Whitty

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
	public class M3AndroidFunctions : ModuleRules
	{
		public M3AndroidFunctions(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			Definitions.Add("WITH_M3AndroidFunctions=1");

			PublicIncludePaths.Add("AndroidFunctions/Public");

			PrivateIncludePaths.Add("M3AndroidFunctions/Private");

            PublicDependencyModuleNames.AddRange(new string[] { "Engine", "Core", "CoreUObject" });
			PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });

			if (Target.Platform == UnrealTargetPlatform.Android)
			{
				PrivateDependencyModuleNames.AddRange(new string[] { "Launch" });
				string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
				AdditionalPropertiesForReceipt.Add(new ReceiptProperty("AndroidPlugin", Path.Combine(PluginPath, "M3AndroidFunctions_UPL.xml")));
			}
		}
	}
}

