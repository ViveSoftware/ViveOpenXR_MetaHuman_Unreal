// Copyright HTC Corporation. All Rights Reserved.

#include "ViveOpenXRAndroidHandInteractionBP.h"
#include "ViveOpenXRHandInteraction.h"

float UViveOpenXRAndroidHandInteractionBP::GetPinchStrength(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return 0;
	return isLeft ? ViveOpenXRHandInteractionModule().HandSelectValue[Side::LEFT] : ViveOpenXRHandInteractionModule().HandSelectValue[Side::RIGHT];
}

FQuat UViveOpenXRAndroidHandInteractionBP::GetPinchRotation(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return FQuat::Identity;
	return isLeft ? ViveOpenXRHandInteractionModule().L_AimRotation.Quaternion() : ViveOpenXRHandInteractionModule().R_AimRotation.Quaternion();
}

FVector UViveOpenXRAndroidHandInteractionBP::GetPinchPosition(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return FVector::ZeroVector;
	return isLeft ? ViveOpenXRHandInteractionModule().L_AimLocation : ViveOpenXRHandInteractionModule().R_AimLocation;
}

bool UViveOpenXRAndroidHandInteractionBP::GetPinchActive(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return false;
	return ViveOpenXRHandInteractionModule().GetAimActive(isLeft);
}

bool UViveOpenXRAndroidHandInteractionBP::GetPinchValid(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return false;
	return ViveOpenXRHandInteractionModule().GetAimValid(isLeft);
}

bool UViveOpenXRAndroidHandInteractionBP::GetPinchTracked(bool isLeft)
{
	if (!ViveOpenXRHandInteractionModule().m_EnableHandInteraction) return false;
	return ViveOpenXRHandInteractionModule().GetAimTracked(isLeft);
}
