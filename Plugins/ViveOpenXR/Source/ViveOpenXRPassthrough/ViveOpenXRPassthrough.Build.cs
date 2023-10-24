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

            // Get the engine path. Ends with "Engine/"
            string engine_path = Path.GetFullPath(Target.RelativeEnginePath);
            string srcrt_path = engine_path + "Source/Runtime/";

            PublicDependencyModuleNames.AddRange(
			   new string[]
			   {
                   "OpenXRHMD",
			   }
		   );

            PrivateIncludePaths.AddRange(
                new string[] {
                    "ViveOpenXRPassthrough/Private/External",
                    engine_path + "Plugins/Runtime/OpenXR/Source/OpenXRHMD/Private/"
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
