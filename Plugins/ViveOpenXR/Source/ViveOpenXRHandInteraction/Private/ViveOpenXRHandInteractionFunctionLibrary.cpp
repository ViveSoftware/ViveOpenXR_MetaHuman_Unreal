// Copyright (c) 2023 HTC Corporation. All Rights Reserved.

#include "ViveOpenXRHandInteractionFunctionLibrary.h"
#include "ViveOpenXRHandInteraction.h"

UViveOpenXRHandInteractionFunctionLibrary::UViveOpenXRHandInteractionFunctionLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UViveOpenXRHandInteractionFunctionLibrary::GetHandInteractionAimPose(bool isRight, bool& valid, FVector& location, FRotator& rotation)
{
	valid = false;
	location = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;

	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	valid = ViveOpenXRHandInteractionModule().CheckAimDataValid(isRight ? 0 : 1);
	if (!valid) return;
	location = isRight ? ViveOpenXRHandInteractionModule().R_AimLocation : ViveOpenXRHandInteractionModule().L_AimLocation;
	rotation = isRight ? ViveOpenXRHandInteractionModule().R_AimRotation : ViveOpenXRHandInteractionModule().L_AimRotation;
	return;
}

void UViveOpenXRHandInteractionFunctionLibrary::GetHandInteractionGripPose(bool isRight, bool& valid, FVector& location, FRotator& rotation)
{
	valid = false;
	location = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;

	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	valid = ViveOpenXRHandInteractionModule().CheckGripDataValid(isRight ? 0 : 1);
	if (!valid) return;
	location = isRight ? ViveOpenXRHandInteractionModule().R_GripLocation : ViveOpenXRHandInteractionModule().L_GripLocation;
	rotation = isRight ? ViveOpenXRHandInteractionModule().R_GripRotation : ViveOpenXRHandInteractionModule().L_GripRotation;
	return;
}

void UViveOpenXRHandInteractionFunctionLibrary::GetHandInteractionSelectValue(bool isRight, bool& valid, float& value)
{
	valid = false;
	value = -1;

	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	valid = ViveOpenXRHandInteractionModule().CheckAimDataValid(isRight ? 0 : 1);
	if (!valid) return;
	value = ViveOpenXRHandInteractionModule().HandSelectValue[isRight ? 0 : 1];
	return;
}

void UViveOpenXRHandInteractionFunctionLibrary::GetHandInteractionSqueezeValue(bool isRight, bool& valid, float& value)
{
	valid = false;
	value = -1;

	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	valid = ViveOpenXRHandInteractionModule().CheckGripDataValid(isRight ? 0 : 1);
	if (!valid) return;
	value = ViveOpenXRHandInteractionModule().HandSqueezeValue[isRight ? 0 : 1];
	return;
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionRightSqueezeValue(float& result)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	result = ViveOpenXRHandInteractionModule().HandSqueezeValue[Side::RIGHT];
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionLeftSqueezeValue(float& result)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	result = ViveOpenXRHandInteractionModule().HandSqueezeValue[Side::LEFT];
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionRightSelectValue(float& result)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	result = ViveOpenXRHandInteractionModule().HandSelectValue[Side::RIGHT];
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionLeftSelectValue(float& result)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	result = ViveOpenXRHandInteractionModule().HandSelectValue[Side::LEFT];
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionRightAimPose(FVector& position, FRotator& rotation)
{
	position = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	if(ViveOpenXRHandInteractionModule().CheckAimDataValid(Side::RIGHT))
	{
		position.X = ViveOpenXRHandInteractionModule().R_AimLocation.X;
		position.Y = ViveOpenXRHandInteractionModule().R_AimLocation.Y;
		position.Z = ViveOpenXRHandInteractionModule().R_AimLocation.Z;
		rotation.Pitch = ViveOpenXRHandInteractionModule().R_AimRotation.Pitch;
		rotation.Roll = ViveOpenXRHandInteractionModule().R_AimRotation.Roll;
		rotation.Yaw = ViveOpenXRHandInteractionModule().R_AimRotation.Yaw;
	}
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionLeftAimPose(FVector& position, FRotator& rotation)
{
	position = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	if (ViveOpenXRHandInteractionModule().CheckAimDataValid(Side::LEFT))
	{
		position.X = ViveOpenXRHandInteractionModule().L_AimLocation.X;
		position.Y = ViveOpenXRHandInteractionModule().L_AimLocation.Y;
		position.Z = ViveOpenXRHandInteractionModule().L_AimLocation.Z;
		rotation.Pitch = ViveOpenXRHandInteractionModule().L_AimRotation.Pitch;
		rotation.Roll = ViveOpenXRHandInteractionModule().L_AimRotation.Roll;
		rotation.Yaw = ViveOpenXRHandInteractionModule().L_AimRotation.Yaw;
	}
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionRightGripPose(FVector& position, FRotator& rotation)
{
	position = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	if (ViveOpenXRHandInteractionModule().CheckGripDataValid(Side::RIGHT))
	{
		position.X = ViveOpenXRHandInteractionModule().R_GripLocation.X;
		position.Y = ViveOpenXRHandInteractionModule().R_GripLocation.Y;
		position.Z = ViveOpenXRHandInteractionModule().R_GripLocation.Z;
		rotation.Pitch = ViveOpenXRHandInteractionModule().R_GripRotation.Pitch;
		rotation.Roll = ViveOpenXRHandInteractionModule().R_GripRotation.Roll;
		rotation.Yaw = ViveOpenXRHandInteractionModule().R_GripRotation.Yaw;
	}
}

void UViveOpenXRHandInteractionFunctionLibrary::HandInteractionLefttGripPose(FVector& position, FRotator& rotation)
{
	position = FVector::ZeroVector;
	rotation = FRotator::ZeroRotator;
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return;
	if (ViveOpenXRHandInteractionModule().CheckGripDataValid(Side::LEFT))
	{
		position.X = ViveOpenXRHandInteractionModule().L_GripLocation.X;
		position.Y = ViveOpenXRHandInteractionModule().L_GripLocation.Y;
		position.Z = ViveOpenXRHandInteractionModule().L_GripLocation.Z;
		rotation.Pitch = ViveOpenXRHandInteractionModule().L_GripRotation.Pitch;
		rotation.Roll = ViveOpenXRHandInteractionModule().L_GripRotation.Roll;
		rotation.Yaw = ViveOpenXRHandInteractionModule().L_GripRotation.Yaw;
	}
}
