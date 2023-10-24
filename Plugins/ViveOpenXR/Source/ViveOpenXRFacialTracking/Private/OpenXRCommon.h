// Copyright (c) 2022 HTC Corporation. All Rights Reserved.
#pragma once

#include "HAL/Platform.h"

#if PLATFORM_ANDROID
#include "External/openxr/openxr.h"
//#include <openxr/openxr_platform.h>
//#include <openxr/openxr_reflection.h>
#else
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>
#include <openxr/openxr_reflection.h>
#endif

#include "IOpenXRHMDModule.h"
#include "IOpenXRExtensionPlugin.h"

#include "OpenXRCore.h"
