// Copyright (c) 2023 HTC Corporation. All Rights Reserved.

using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class ViveOpenXRDisplayRefreshRate : ModuleRules
	{

		public ViveOpenXRDisplayRefreshRate(ReadOnlyTargetRules Target) : base(Target)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"ViveOpenXRHMD",
					"OpenXRHMD",
				}
			);
		}
	}
}
