// Copyright (c) 2023 HTC Corporation. All Rights Reserved.

#pragma once

#include "IOpenXRExtensionPlugin.h"
#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "OpenXRCore.h"
#include "InputCoreTypes.h"

DECLARE_LOG_CATEGORY_EXTERN(LogViveOpenXRHandInteraction, Log, All);

namespace Side
{
	const int RIGHT = 0;
	const int LEFT = 1;
	const int COUNT = 2;
}
namespace Type
{
	const int SQUEEZE = 0;
	const int SELECT = 1;
	const int AIM = 2;
	const int GRIP = 3;
	const int COUNT = 4;
}
namespace Path
{
	const int RIGHT_SQUEEZE = 0;
	const int LEFT_SQUEEZE = 1;
	const int RIGHT_SSELECT = 2;
	const int LEFT_SELECT = 3;
	const int RIGHT_AIM = 4;
	const int LEFT_AIM = 5;
	const int RIGHT_GRIP = 6;
	const int LEFT_GRIP = 7;
	const int COUNT = 8;
}

class FViveOpenXRHandInteractionModule : public IModuleInterface, public IOpenXRExtensionPlugin
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	virtual bool GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions) override;
	virtual bool GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics) override;
	//virtual void AddActions(XrInstance InInstance, TFunction<XrAction(XrActionType InActionType, const FName& InName, const TArray<XrPath>& InSubactionPaths)> AddAction) override;
	virtual void AttachActionSets(TSet<XrActionSet>& OutActionSets) override;
	virtual void GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets) override;
	virtual void PostCreateInstance(XrInstance InInstance) override;
	virtual const void* OnBeginSession(XrSession InSession, const void* InNext) override;
	virtual void PostSyncActions(XrSession InSession) override;
	virtual void UpdateDeviceLocations(XrSession InSession, XrTime DisplayTime, XrSpace TrackingSpace) override;

	TArray<float>HandSqueezeValue;
	TArray<float>HandSelectValue;
	TArray<FVector>AimLocation;
	TArray<FVector>GripLocation;
	TArray<FRotator>AimRotation;
	TArray<FRotator>GripRotation;
	FVector R_AimLocation;
	FVector L_AimLocation;
	FVector R_GripLocation;
	FVector L_GripLocation;
	FRotator R_AimRotation;
	FRotator L_AimRotation;
	FRotator R_GripRotation;
	FRotator L_GripRotation;
	bool m_EnableHandInteraction = true;

	bool CheckAimDataValid(int HandSide)
	{
		bool isLeft = (HandSide == Side::LEFT);
		return GetAimActive(isLeft) || GetAimValid(isLeft) || GetAimTracked(isLeft);
	}

	bool CheckGripDataValid(int HandSide)
	{
		bool isLeft = (HandSide == Side::LEFT);
		return GetGripActive(isLeft) || GetGripValid(isLeft) || GetGripTracked(isLeft);
	}

	bool GetAimActive(bool isLeft)
	{
		return isLeft ? LeftAimStatePose.isActive > 0 : RightAimStatePose.isActive > 0;
	}

	bool GetGripActive(bool isLeft)
	{
		return isLeft ? LeftGripStatePose.isActive > 0 : RightGripStatePose.isActive > 0;
	}

	bool GetAimValid(bool isLeft)
	{
		if (!GetAimActive(isLeft)) { return false; }

		auto locationFlags = isLeft ? LeftAimSpaceLocation.locationFlags : RightAimSpaceLocation.locationFlags;
		return locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT &&
			locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT;
	}

	bool GetGripValid(bool isLeft)
	{
		if (!GetGripActive(isLeft)) { return false; }

		auto locationFlags = isLeft ? LeftGripSpaceLocation.locationFlags : RightGripSpaceLocation.locationFlags;
		return locationFlags & XR_SPACE_LOCATION_ORIENTATION_VALID_BIT &&
			locationFlags & XR_SPACE_LOCATION_POSITION_VALID_BIT;
	}

	bool GetAimTracked(bool isLeft)
	{
		if (!GetAimActive(isLeft)) { return false; }

		auto locationFlags = isLeft ? LeftAimSpaceLocation.locationFlags : RightAimSpaceLocation.locationFlags;
		return locationFlags & XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT &&
			locationFlags & XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
	}

	bool GetGripTracked(bool isLeft)
	{
		if (!GetGripActive(isLeft)) { return false; }

		auto locationFlags = isLeft ? LeftGripSpaceLocation.locationFlags : RightGripSpaceLocation.locationFlags;
		return locationFlags & XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT &&
			locationFlags & XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
	}

private:
	class IXRTrackingSystem* XRTrackingSystem = nullptr;
	XrActionsSyncInfo SyncInfo{ XR_TYPE_ACTIONS_SYNC_INFO };
	XrSpaceLocation RightAimSpaceLocation{ XR_TYPE_SPACE_LOCATION };
	XrSpaceLocation LeftAimSpaceLocation{ XR_TYPE_SPACE_LOCATION };
	XrSpaceLocation RightGripSpaceLocation{ XR_TYPE_SPACE_LOCATION };
	XrSpaceLocation LeftGripSpaceLocation{ XR_TYPE_SPACE_LOCATION };
	XrActionStatePose RightAimStatePose{ XR_TYPE_ACTION_STATE_POSE };
	XrActionStatePose LeftAimStatePose{ XR_TYPE_ACTION_STATE_POSE };
	XrActionStatePose RightGripStatePose{ XR_TYPE_ACTION_STATE_POSE };
	XrActionStatePose LeftGripStatePose{ XR_TYPE_ACTION_STATE_POSE };
	TArray<XrPath> SubactionPaths;
	TArray<XrAction>R_HandInteraction;
	TArray<XrAction>L_HandInteraction;
	TArray<XrSpace>AimSpace;
	TArray<XrSpace>GripSpace;
	bool bSessionStarted = false;

	XrInstance Instance = XR_NULL_HANDLE;
	XrActionSet HandInteractionActionSet = XR_NULL_HANDLE;
	
};

inline FViveOpenXRHandInteractionModule& ViveOpenXRHandInteractionModule()
{
	return FModuleManager::Get().GetModuleChecked<FViveOpenXRHandInteractionModule>("ViveOpenXRHandInteraction");
}