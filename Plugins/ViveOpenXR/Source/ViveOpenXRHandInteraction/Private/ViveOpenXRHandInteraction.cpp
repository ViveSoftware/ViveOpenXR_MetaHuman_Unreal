// Copyright (c) 2023 HTC Corporation. All Rights Reserved.

#include "ViveOpenXRHandInteraction.h"
#include "IXRTrackingSystem.h"
#include "IOpenXRExtensionPlugin.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
#include "OpenXRCore.h"
#include "InputCoreTypes.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Misc/ConfigCacheIni.h"

#define LOCTEXT_NAMESPACE "FViveOpenXRHandInteractionModule"

#if WITH_EDITOR
#include "Editor/EditorEngine.h"
#include "Editor.h"
#endif

DEFINE_LOG_CATEGORY(LogViveOpenXRHandInteraction);

void FViveOpenXRHandInteractionModule::StartupModule()
{
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("StartupModule() Entry."));
	
	check(GConfig && GConfig->IsReadyForUse());
	FString modeName;
	if (GConfig->GetString(TEXT("/Script/ViveOpenXRRuntimeSettings.ViveOpenXRRuntimeSettings"), TEXT("bEnableHandInteraction"), modeName, GEngineIni))
	{
		if (modeName.Equals("False"))
		{
			m_EnableHandInteraction = false;
		}
		else if (modeName.Equals("True"))
		{
			m_EnableHandInteraction = true;
		}
	}

	if (m_EnableHandInteraction)
	{
		UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("Enable Hand Interaction."));
	}
	else
	{
		UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("Disable Hand Interaction."));
	}

	RegisterOpenXRExtensionModularFeature();
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("StartupModule() Finished."));
}

void FViveOpenXRHandInteractionModule::ShutdownModule()
{
	UnregisterOpenXRExtensionModularFeature();
}

bool FViveOpenXRHandInteractionModule::GetRequiredExtensions(TArray<const ANSICHAR*>& OutExtensions)
{
	if (m_EnableHandInteraction)
	{
		UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("GetRequiredExtensions() XR_HTC_hand_interaction."));

		OutExtensions.Add("XR_HTC_hand_interaction");
	}

	return true;
}

bool FViveOpenXRHandInteractionModule::GetInteractionProfile(XrInstance InInstance, FString& OutKeyPrefix, XrPath& OutPath, bool& OutHasHaptics)
{
	if (!m_EnableHandInteraction) return false;
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("GetInteractionProfile() /interaction_profiles/htc/hand_interaction."));


	OutKeyPrefix = "HandInteraction";
	OutHasHaptics = false;
	return xrStringToPath(InInstance, "/interaction_profiles/htc/hand_interaction", &OutPath) == XR_SUCCESS;
}

//void FViveOpenXRHandInteractionModule::AddActions(XrInstance InInstance, TFunction<XrAction(XrActionType InActionType, const FName& InName, const TArray<XrPath>& InSubactionPaths)> AddAction)
//{
//	if (!m_EnableHandInteraction) return ;
//
//	XrPath HandInteractionProfilePath = XR_NULL_PATH;
//	XR_ENSURE(xrStringToPath(InInstance, "/interaction_profiles/htc/hand_interaction", &HandInteractionProfilePath));
//
//	XrPath RightHand = XR_NULL_PATH;
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/right", &RightHand));
//
//	XrPath LeftHand = XR_NULL_PATH;
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/left", &LeftHand));
//
//	SubactionPaths.Emplace(RightHand);
//	SubactionPaths.Emplace(LeftHand);
//
//	HandInteraction.Emplace(AddAction(XR_ACTION_TYPE_FLOAT_INPUT, "HandInteractionSqueeze", SubactionPaths));
//	HandInteraction.Emplace(AddAction(XR_ACTION_TYPE_FLOAT_INPUT, "HandInteractionSelect", SubactionPaths));
//	HandInteraction.Emplace(AddAction(XR_ACTION_TYPE_POSE_INPUT, "HandInteractionAimPose", SubactionPaths));
//	HandInteraction.Emplace(AddAction(XR_ACTION_TYPE_POSE_INPUT, "HandInteractionGripPose", SubactionPaths));
//
//	for (int i = 0; i < 4; ++i)
//	{
//		if (HandInteraction[i] == XR_NULL_HANDLE)
//		{
//			return;
//		}
//	}
//
//	TArray<XrPath>HandInteractionPaths;
//
//	for (int i = 0; i < 8; ++i)
//		HandInteractionPaths.Emplace(XR_NULL_PATH);
//
//	// Hand interaction vlaue
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/right/input/squeeze/value", &HandInteractionPaths[Path::RIGHT_SQUEEZE]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/left/input/squeeze/value", &HandInteractionPaths[Path::LEFT_SQUEEZE]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/right/input/select/value", &HandInteractionPaths[Path::RIGHT_SSELECT]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/left/input/squeeze/value", &HandInteractionPaths[Path::LEFT_SELECT]));
//	// Hand interaction pose
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/right/input/aim/pose", &HandInteractionPaths[Path::RIGHT_AIM]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/left/input/aim/pose", &HandInteractionPaths[Path::LEFT_AIM]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/right/input/grip/pose", &HandInteractionPaths[Path::RIGHT_GRIP]));
//	XR_ENSURE(xrStringToPath(InInstance, "/user/hand_htc/left/input/grip/pose", &HandInteractionPaths[Path::LEFT_GRIP]));
//
//	std::vector<XrActionSuggestedBinding> Bindings
//	{
//		{
//			{HandInteraction[Type::SQUEEZE], HandInteractionPaths[Path::RIGHT_SQUEEZE]},
//			{HandInteraction[Type::SQUEEZE], HandInteractionPaths[Path::LEFT_SQUEEZE]},
//			{HandInteraction[Type::SELECT], HandInteractionPaths[Path::RIGHT_SSELECT]},
//			{HandInteraction[Type::SELECT], HandInteractionPaths[Path::LEFT_SELECT]},
//			{HandInteraction[Type::AIM], HandInteractionPaths[Path::RIGHT_AIM]},
//			{HandInteraction[Type::AIM], HandInteractionPaths[Path::LEFT_AIM]},
//			{HandInteraction[Type::GRIP], HandInteractionPaths[Path::RIGHT_GRIP]},
//			{HandInteraction[Type::GRIP], HandInteractionPaths[Path::LEFT_GRIP]}
//		}
//	};
//
//	XrInteractionProfileSuggestedBinding SuggestedBindings{ XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING };
//	SuggestedBindings.interactionProfile = HandInteractionProfilePath;
//	SuggestedBindings.suggestedBindings = Bindings.data();
//	SuggestedBindings.countSuggestedBindings = (uint32_t)Bindings.size();
//	XR_ENSURE(xrSuggestInteractionProfileBindings(InInstance, &SuggestedBindings));
//
//}

void FViveOpenXRHandInteractionModule::AttachActionSets(TSet<XrActionSet>& OutActionSets)
{
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Entry."));
	if (!m_EnableHandInteraction) return;
	
	check(Instance != XR_NULL_HANDLE);

	XrPath RightHand = XR_NULL_PATH;
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/right", &RightHand));

	XrPath LeftHand = XR_NULL_PATH;
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/left", &LeftHand));

	SubactionPaths.Emplace(RightHand);
	SubactionPaths.Emplace(LeftHand);

	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Create ActionSet."));

	//Create ActionSet
	if (HandInteractionActionSet != XR_NULL_HANDLE)
	{
		xrDestroyActionSet(HandInteractionActionSet);
		HandInteractionActionSet = XR_NULL_HANDLE;
	}
	{
		XrActionSetCreateInfo Info;
		Info.type = XR_TYPE_ACTION_SET_CREATE_INFO;
		Info.next = nullptr;
		FCStringAnsi::Strcpy(Info.actionSetName, XR_MAX_ACTION_SET_NAME_SIZE, "viveopenxrhandinteractionactionset");
		FCStringAnsi::Strcpy(Info.localizedActionSetName, XR_MAX_LOCALIZED_ACTION_SET_NAME_SIZE, "VIVE OpenXR Hand Interaction Action Set");
		Info.priority = 0;
		XR_ENSURE(xrCreateActionSet(Instance, &Info, &HandInteractionActionSet));
	}

	TArray<XrPath>HandInteractionPaths;
	for (int i = 0; i < 8; ++i)
		HandInteractionPaths.Emplace(XR_NULL_PATH);

	// Hand interaction vlaue
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/right/input/squeeze/value", &HandInteractionPaths[Path::RIGHT_SQUEEZE]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/left/input/squeeze/value", &HandInteractionPaths[Path::LEFT_SQUEEZE]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/right/input/select/value", &HandInteractionPaths[Path::RIGHT_SSELECT]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/left/input/select/value", &HandInteractionPaths[Path::LEFT_SELECT]));
	// Hand interaction pose
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/right/input/aim/pose", &HandInteractionPaths[Path::RIGHT_AIM]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/left/input/aim/pose", &HandInteractionPaths[Path::LEFT_AIM]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/right/input/grip/pose", &HandInteractionPaths[Path::RIGHT_GRIP]));
	XR_ENSURE(xrStringToPath(Instance, "/user/hand_htc/left/input/grip/pose", &HandInteractionPaths[Path::LEFT_GRIP]));

	for (int i = 0; i < 4; ++i)
	{
		R_HandInteraction.Emplace(XR_NULL_HANDLE);
		L_HandInteraction.Emplace(XR_NULL_HANDLE);
	}

	//UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Create XrActionSuggestedBinding."));

	//TArray<XrActionSuggestedBinding> Bindings
	//{
	//	{
	//		{ R_HandInteraction[Type::SQUEEZE], HandInteractionPaths[Path::RIGHT_SQUEEZE]},
	//		{ L_HandInteraction[Type::SQUEEZE], HandInteractionPaths[Path::LEFT_SQUEEZE] },
	//		{ R_HandInteraction[Type::SELECT], HandInteractionPaths[Path::RIGHT_SSELECT] },
	//		{ L_HandInteraction[Type::SELECT], HandInteractionPaths[Path::LEFT_SELECT] },
	//		{ R_HandInteraction[Type::AIM], HandInteractionPaths[Path::RIGHT_AIM] },
	//		{ L_HandInteraction[Type::AIM], HandInteractionPaths[Path::LEFT_AIM] },
	//		{ R_HandInteraction[Type::GRIP], HandInteractionPaths[Path::RIGHT_GRIP] },
	//		{ L_HandInteraction[Type::GRIP], HandInteractionPaths[Path::LEFT_GRIP] }
	//	}
	//};

	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Create Action lambda."));

	//Create Actions lambda
	auto AddAction = [&](XrActionSet& InActionSet, XrAction& OutAction, XrActionType InActionType, const FName& InName, const TArray<XrPath>& InSubactionPaths)
	{
		check(InActionSet != XR_NULL_HANDLE);
		if (OutAction != XR_NULL_HANDLE) {
			xrDestroyAction(OutAction);
			OutAction = XR_NULL_HANDLE;
		}

		char ActionName[NAME_SIZE];
		InName.GetPlainANSIString(ActionName);

		XrActionCreateInfo Info;
		Info.type = XR_TYPE_ACTION_CREATE_INFO;
		Info.next = nullptr;
		Info.actionType = InActionType;
		Info.countSubactionPaths = InSubactionPaths.Num();
		Info.subactionPaths = InSubactionPaths.GetData();
		FCStringAnsi::Strcpy(Info.actionName, XR_MAX_ACTION_NAME_SIZE, ActionName);
		FCStringAnsi::Strcpy(Info.localizedActionName, XR_MAX_LOCALIZED_ACTION_NAME_SIZE, ActionName);
		XR_ENSURE(xrCreateAction(InActionSet, &Info, &OutAction));
	};

	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Create suggested bindings."));
	// Create suggested bindings
	XrPath HandInteractionProfilePath = XR_NULL_PATH;
	XR_ENSURE(xrStringToPath(Instance, "/interaction_profiles/htc/hand_interaction", &HandInteractionProfilePath));

	//TArray<XrPath> subactionPaths;
	XrActionSuggestedBinding bindings[8];


	// 0. right squeeze value
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 0. /user/hand_htc/right/input/squeeze/value."));
	AddAction(HandInteractionActionSet, R_HandInteraction[Type::SQUEEZE], XR_ACTION_TYPE_FLOAT_INPUT, "right_squeeze_value", SubactionPaths);
	if (R_HandInteraction[Type::SQUEEZE] == XR_NULL_HANDLE) { return; }
	bindings[0].action = R_HandInteraction[Type::SQUEEZE];
	bindings[0].binding = HandInteractionPaths[Path::RIGHT_SQUEEZE];

	// 1. left squeeze value
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 1. /user/hand_htc/left/input/squeeze/value."));
	AddAction(HandInteractionActionSet, L_HandInteraction[Type::SQUEEZE], XR_ACTION_TYPE_FLOAT_INPUT, "left_squeeze_value", SubactionPaths);
	if (L_HandInteraction[Type::SQUEEZE] == XR_NULL_HANDLE) { return; }
	bindings[1].action = L_HandInteraction[Type::SQUEEZE];
	bindings[1].binding = HandInteractionPaths[Path::LEFT_SQUEEZE];

	// 2. right select value
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 2. /user/hand_htc/right/input/select/value."));
	AddAction(HandInteractionActionSet, R_HandInteraction[Type::SELECT], XR_ACTION_TYPE_FLOAT_INPUT, "right_select_value", SubactionPaths);
	if (R_HandInteraction[Type::SELECT] == XR_NULL_HANDLE) { return; }
	bindings[2].action = R_HandInteraction[Type::SELECT];
	bindings[2].binding = HandInteractionPaths[Path::RIGHT_SSELECT];

	// 3. left select value
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 3. /user/hand_htc/left/input/select/value."));
	AddAction(HandInteractionActionSet, L_HandInteraction[Type::SELECT], XR_ACTION_TYPE_FLOAT_INPUT, "left_select_value", SubactionPaths);
	if (L_HandInteraction[Type::SELECT] == XR_NULL_HANDLE) { return; }
	bindings[3].action = L_HandInteraction[Type::SELECT];
	bindings[3].binding = HandInteractionPaths[Path::LEFT_SELECT];

	// 4. right aim pose
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 4. /user/hand_htc/right/input/aim/pose."));
	AddAction(HandInteractionActionSet, R_HandInteraction[Type::AIM], XR_ACTION_TYPE_POSE_INPUT, "right_aim_pose", SubactionPaths);
	if (R_HandInteraction[Type::AIM] == XR_NULL_HANDLE) { return; }
	bindings[4].action = R_HandInteraction[Type::AIM];
	bindings[4].binding = HandInteractionPaths[Path::RIGHT_AIM];

	// 5. left aim pose
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 5. /user/hand_htc/left/input/aim/pose."));
	AddAction(HandInteractionActionSet, L_HandInteraction[Type::AIM], XR_ACTION_TYPE_POSE_INPUT, "left_aim_pose", SubactionPaths);
	if (L_HandInteraction[Type::AIM] == XR_NULL_HANDLE) { return; }
	bindings[5].action = L_HandInteraction[Type::AIM];
	bindings[5].binding = HandInteractionPaths[Path::LEFT_AIM];

	// 6. right grip pose
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 6. /user/hand_htc/right/input/grip/pose."));
	AddAction(HandInteractionActionSet, R_HandInteraction[Type::GRIP], XR_ACTION_TYPE_POSE_INPUT, "right_grip_pose", SubactionPaths);
	if (R_HandInteraction[Type::GRIP] == XR_NULL_HANDLE) { return; }
	bindings[6].action = R_HandInteraction[Type::GRIP];
	bindings[6].binding = HandInteractionPaths[Path::RIGHT_GRIP];

	// 7. left grip pose
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() 7. /user/hand_htc/left/input/grip/pose."));
	AddAction(HandInteractionActionSet, L_HandInteraction[Type::GRIP], XR_ACTION_TYPE_POSE_INPUT, "left_grip_pose", SubactionPaths);
	if (L_HandInteraction[Type::GRIP] == XR_NULL_HANDLE) { return; }
	bindings[7].action = L_HandInteraction[Type::GRIP];
	bindings[7].binding = HandInteractionPaths[Path::LEFT_GRIP];

	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() Create XrInteractionProfileSuggestedBinding."));
	XrInteractionProfileSuggestedBinding SuggestedBindings{ XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING };
	SuggestedBindings.interactionProfile = HandInteractionProfilePath;
	SuggestedBindings.suggestedBindings = bindings;
	SuggestedBindings.countSuggestedBindings = 8;
	XR_ENSURE(xrSuggestInteractionProfileBindings(Instance, &SuggestedBindings));

	OutActionSets.Add(HandInteractionActionSet);
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("AttachActionSets() finished."));
}

void FViveOpenXRHandInteractionModule::GetActiveActionSetsForSync(TArray<XrActiveActionSet>& OutActiveSets)
{
	if (!m_EnableHandInteraction) return;

	check(HandInteractionActionSet != XR_NULL_HANDLE);
	OutActiveSets.Add(XrActiveActionSet{ HandInteractionActionSet, XR_NULL_PATH });
}

void FViveOpenXRHandInteractionModule::PostCreateInstance(XrInstance InInstance)
{
	Instance = InInstance;
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("PostCreateInstance() finished."));
}

const void* FViveOpenXRHandInteractionModule::OnBeginSession(XrSession InSession, const void* InNext)
{
	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("OnBeginSession() entry."));
	if (!m_EnableHandInteraction)
	{
		UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("OnBeginSession() m_EnableHandInteraction is false."));
		return InNext;
	}

	static FName SystemName(TEXT("OpenXR"));
	if (GEngine->XRSystem.IsValid() && (GEngine->XRSystem->GetSystemName() == SystemName))
	{
		XRTrackingSystem = GEngine->XRSystem.Get();
	}

	AimSpace.Empty();
	GripSpace.Empty();
	HandSqueezeValue.Empty();
	HandSelectValue.Empty();

	for (int i = 0; i < 2; ++i)
	{
		AimSpace.Emplace(XR_NULL_HANDLE);
		GripSpace.Emplace(XR_NULL_HANDLE);
		HandSqueezeValue.Emplace(0);
		HandSelectValue.Emplace(0);
	}

	// Aim
	XrActionSpaceCreateInfo CreateRightAimSpaceInfo{ XR_TYPE_ACTION_SPACE_CREATE_INFO };
	CreateRightAimSpaceInfo.action = R_HandInteraction[Type::AIM];
	CreateRightAimSpaceInfo.poseInActionSpace = ToXrPose(FTransform::Identity);
	CreateRightAimSpaceInfo.subactionPath = SubactionPaths[Side::RIGHT];
	XR_ENSURE(xrCreateActionSpace(InSession, &CreateRightAimSpaceInfo, &AimSpace[Side::RIGHT]));

	XrActionSpaceCreateInfo CreateLeftAimSpaceInfo{ XR_TYPE_ACTION_SPACE_CREATE_INFO };
	CreateLeftAimSpaceInfo.action = L_HandInteraction[Type::AIM];
	CreateLeftAimSpaceInfo.poseInActionSpace = ToXrPose(FTransform::Identity);
	CreateLeftAimSpaceInfo.subactionPath = SubactionPaths[Side::LEFT];
	XR_ENSURE(xrCreateActionSpace(InSession, &CreateLeftAimSpaceInfo, &AimSpace[Side::LEFT]));

	// Grip
	XrActionSpaceCreateInfo CreateRightGripSpaceInfo{ XR_TYPE_ACTION_SPACE_CREATE_INFO };
	CreateRightGripSpaceInfo.action = R_HandInteraction[Type::GRIP];
	CreateRightGripSpaceInfo.poseInActionSpace = ToXrPose(FTransform::Identity);
	CreateRightGripSpaceInfo.subactionPath = SubactionPaths[Side::RIGHT];
	XR_ENSURE(xrCreateActionSpace(InSession, &CreateRightGripSpaceInfo, &GripSpace[Side::RIGHT]));

	XrActionSpaceCreateInfo CreateLefttGripSpaceInfo{ XR_TYPE_ACTION_SPACE_CREATE_INFO };
	CreateLefttGripSpaceInfo.action = L_HandInteraction[Type::GRIP];
	CreateLefttGripSpaceInfo.poseInActionSpace = ToXrPose(FTransform::Identity);
	CreateLefttGripSpaceInfo.subactionPath = SubactionPaths[Side::LEFT];
	XR_ENSURE(xrCreateActionSpace(InSession, &CreateLefttGripSpaceInfo, &GripSpace[Side::LEFT]));

	SyncInfo.countActiveActionSets = 0;
	SyncInfo.activeActionSets = XR_NULL_HANDLE;

	bSessionStarted = true;

	UE_LOG(LogViveOpenXRHandInteraction, Log, TEXT("OnBeginSession() finished."));

	return InNext;
}

void FViveOpenXRHandInteractionModule::PostSyncActions(XrSession InSession)
{
	if (!m_EnableHandInteraction) return;

	// Aim
	XrActionStateGetInfo GetRightAimStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
	GetRightAimStateInfo.action = R_HandInteraction[Type::AIM];
	GetRightAimStateInfo.subactionPath = SubactionPaths[Side::RIGHT];
	XR_ENSURE(xrGetActionStatePose(InSession, &GetRightAimStateInfo, &RightAimStatePose));

	XrActionStateGetInfo GetLeftAimStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
	GetLeftAimStateInfo.action = L_HandInteraction[Type::AIM];
	GetLeftAimStateInfo.subactionPath = SubactionPaths[Side::LEFT];
	XR_ENSURE(xrGetActionStatePose(InSession, &GetLeftAimStateInfo, &LeftAimStatePose));

	// Grip
	XrActionStateGetInfo GetRightGripStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
	GetRightGripStateInfo.action = R_HandInteraction[Type::GRIP];
	GetRightGripStateInfo.subactionPath = SubactionPaths[Side::RIGHT];
	XR_ENSURE(xrGetActionStatePose(InSession, &GetRightGripStateInfo, &RightGripStatePose));

	XrActionStateGetInfo GetLeftGripStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
	GetLeftGripStateInfo.action = L_HandInteraction[Type::GRIP];
	GetLeftGripStateInfo.subactionPath = SubactionPaths[Side::LEFT];
	XR_ENSURE(xrGetActionStatePose(InSession, &GetLeftGripStateInfo, &LeftGripStatePose));

	for (int i = 0; i < 2; ++i)
	{
		// Squeeze
		XrActionStateGetInfo SqueezeStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
		SqueezeStateInfo.action = (i == Side::RIGHT) ? R_HandInteraction[Type::SQUEEZE] : L_HandInteraction[Type::SQUEEZE];
		SqueezeStateInfo.subactionPath = SubactionPaths[i];
		XrActionStateFloat SqueezeValue{ XR_TYPE_ACTION_STATE_FLOAT };
		XR_ENSURE(xrGetActionStateFloat(InSession, &SqueezeStateInfo, &SqueezeValue));
		if (SqueezeValue.isActive == XR_TRUE)
		{
			if (i == Side::RIGHT)
			{
				HandSqueezeValue[Side::RIGHT] = SqueezeValue.currentState;
			}
			else if (i == Side::LEFT)
			{
				HandSqueezeValue[Side::LEFT] = SqueezeValue.currentState;
			}
		}

		// Select
		XrActionStateGetInfo SelectStateInfo{ XR_TYPE_ACTION_STATE_GET_INFO };
		SelectStateInfo.action = (i == Side::RIGHT) ? R_HandInteraction[Type::SELECT] : L_HandInteraction[Type::SELECT];
		SelectStateInfo.subactionPath = SubactionPaths[i];
		XrActionStateFloat SelectValue{ XR_TYPE_ACTION_STATE_FLOAT };
		XR_ENSURE(xrGetActionStateFloat(InSession, &SelectStateInfo, &SelectValue));
		if (SelectValue.isActive == XR_TRUE)
		{
			if (i == Side::RIGHT)
			{
				HandSelectValue[Side::RIGHT] = SelectValue.currentState;
			}
			else if (i == Side::LEFT)
			{
				HandSelectValue[Side::LEFT] = SelectValue.currentState;
			}
		}
	}
}

void FViveOpenXRHandInteractionModule::UpdateDeviceLocations(XrSession InSession, XrTime DisplayTime, XrSpace TrackingSpace)
{
	if (!m_EnableHandInteraction) return;

	const float WorldToMetersScale = XRTrackingSystem->GetWorldToMetersScale();

	if (RightAimStatePose.isActive) {
		XR_ENSURE(xrLocateSpace(AimSpace[Side::RIGHT], TrackingSpace, DisplayTime, &RightAimSpaceLocation));
	}
	if (LeftAimStatePose.isActive) {
		XR_ENSURE(xrLocateSpace(AimSpace[Side::LEFT], TrackingSpace, DisplayTime, &LeftAimSpaceLocation));
	}
	if (RightGripStatePose.isActive) {
		XR_ENSURE(xrLocateSpace(GripSpace[Side::RIGHT], TrackingSpace, DisplayTime, &RightGripSpaceLocation));
	}
	if (LeftGripStatePose.isActive) {
		XR_ENSURE(xrLocateSpace(GripSpace[Side::LEFT], TrackingSpace, DisplayTime, &LeftGripSpaceLocation));
	}

	const FTransform R_AimTransform = ToFTransform(RightAimSpaceLocation.pose, WorldToMetersScale);
	const FTransform L_AimTransform = ToFTransform(LeftAimSpaceLocation.pose, WorldToMetersScale);
	const FTransform R_GripTransform = ToFTransform(RightGripSpaceLocation.pose, WorldToMetersScale);
	const FTransform L_GripTransform = ToFTransform(LeftGripSpaceLocation.pose, WorldToMetersScale);
	
	R_AimLocation = R_AimTransform.GetLocation();
	L_AimLocation = L_AimTransform.GetLocation();
	R_GripLocation = R_GripTransform.GetLocation();
	L_GripLocation = L_GripTransform.GetLocation();
	R_AimRotation = R_AimTransform.GetRotation().Rotator();
	L_AimRotation = L_AimTransform.GetRotation().Rotator();
	R_GripRotation = R_GripTransform.GetRotation().Rotator();
	L_GripRotation = L_GripTransform.GetRotation().Rotator();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FViveOpenXRHandInteractionModule, ViveOpenXRHandInteraction)