// Copyright (c) 2022 HTC Corporation. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Engine/EngineTypes.h"

DECLARE_LOG_CATEGORY_EXTERN(LogViveOpenXRSettings, Log, All);

#include "ViveOpenXRRuntimeSettings.generated.h"


UCLASS(config = Engine, defaultconfig)
class VIVEOPENXRRUNTIMESETTINGS_API UViveOpenXRRuntimeSettings : public UObject
{
public:
    GENERATED_BODY()

    static UViveOpenXRRuntimeSettings* Get();

    void PostInitProperties();

#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif	  // WITH_EDITOR

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Controller",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Cosmos Controller",
        Tooltip = "The OpenXR extension XR_HTC_vive_cosmos_controller_interaction enables the use of HTC Vive Cosmos Controllers interaction profiles in OpenXR. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Cosmos Controller\"."))
    bool bEnableCosmosController = true;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Controller",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Focus3 Controller",
        Tooltip = "The OpenXR extension XR_HTC_vive_focus3_controller_interaction enables the use of HTC Vive Focus3 Controllers interaction profiles in OpenXR. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Focus3 Controller\""))
    bool bEnableFocus3Controller = true;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Facial Tracking",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Facial Tracking",
        Tooltip = "To help software developers create an application with actual facial expressions on 3D avatars with the OpenXR facial tracing extension XR_HTC_facial_trackin. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Facial Tracking\"."))
    bool bEnableFacialTracking = false;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Scene Understanding",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Scene Understanding",
        Tooltip = "Demonstrate configuring, calculating and generating mesh of surrouding environments by the OpenXR scene understanding extension XR_MSFT_scene_understanding. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Scene Understanding\"."))
    bool bEnableSceneUnderstanding = false;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Hand Interaction",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Hand Interaction",
        Tooltip = "To help software developers create hand interactions with the OpenXR hand interaction extension XR_HTC_hand_interaction. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Hand Interaction\"."))
    bool bEnableHandInteraction = true;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Passthrough",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Passthrough",
        Tooltip = "To support the OpenXR extension XR_HTC_passthrough feature. Only Passthrough Underlay is available for now. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Passthrough\"."))
    bool bEnablePassthrough = false;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Wrist Tracker",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Wrist Tracker",
        Tooltip = "The OpenXR extension XR_HTC_vive_wrist_tracker_interaction enables the use of HTC Wrist Tracker interaction profiles in OpenXR. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Wrist Tracker\"."))
    bool bEnableWristTracker = false;

    //Auto-generate to detect is OpenXRHandTracking plugin enabled. This property is use for modifying AndroidManifest.xml
    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Controller",  // Add category cause package complains about it
        Meta = (EditConditionHides, Editcondition="false"))
    bool bEnableHandTracking = false;

    UPROPERTY(GlobalConfig, EditAnywhere, Category = "Display Refresh Rate",
        Meta = (ConfigRestartRequired = true, DisplayName = "Enable Display Refresh Rate",
        Tooltip = "The OpenXR extension XR_FB_display_refresh_rate support dynamically adjusting the display refresh rate in order to improve the overall user experience. \nNOTE: You need to restart the engine to apply new settings after clicking \"Enable Display Refresh Rate\"."))
    bool bEnableDisplayRefreshRate = false;

private:
    static class UViveOpenXRRuntimeSettings* ViveOpenXRRuntimeSettingsSingleton;
};
