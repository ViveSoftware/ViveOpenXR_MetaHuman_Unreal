// Copyright (c) 2022 HTC Corporation. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{
    public class ViveOpenXRPassthrough: ModuleRules
    {

        public ViveOpenXRPassthrough(ReadOnlyTargetRules Target) 
				: base(Target)
        {
            //PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PrivatePCHHeaderFile = @"Private\OpenXRCommon.h";

            PublicDependencyModuleNames.AddRange(
			   new string[]
			   {
                   "OpenXRHMD",
			   }
		   );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "ViveOpenXRPassthrough/Private/External"
                }
                );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Core",
                    "CoreUObject",
                    "Engine",
                    "ViveOpenXRHMD",
                    "InputCore",
					"HeadMountedDisplay",
                    "OpenXRHMD",
                }
				);

            AddEngineThirdPartyPrivateStaticDependencies(Target, "OpenXR");

            if (Target.bBuildEditor == true)
            {
                PrivateDependencyModuleNames.Add("UnrealEd");
            }
        }
    }
}
