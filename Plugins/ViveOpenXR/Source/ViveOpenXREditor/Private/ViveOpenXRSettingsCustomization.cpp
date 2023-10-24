// Copyright (c) 2022 HTC Corporation. All Rights Reserved.


#include "ViveOpenXRSettingsCustomization.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Input/SButton.h"
#include "DetailWidgetRow.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Misc/Paths.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "OpenXRViveSettings"
TSharedRef<IDetailCustomization> FViveOpenXRSettingsCustomization::MakeInstance()
{
	return MakeShareable(new FViveOpenXRSettingsCustomization);
}

void FViveOpenXRSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	IDetailCategoryBuilder& ControllerCategory = DetailLayout.EditCategory(TEXT("Controller"));
	IDetailCategoryBuilder& FacialTrackingCategory = DetailLayout.EditCategory(TEXT("Facial Tracking"));
	IDetailCategoryBuilder& HandInteractionCategory = DetailLayout.EditCategory(TEXT("Hand Interaction"));
	IDetailCategoryBuilder& PassthroughCategory = DetailLayout.EditCategory(TEXT("Passthrough"));
	IDetailCategoryBuilder& WristTrackerCategory = DetailLayout.EditCategory(TEXT("Wrist Tracker"));
	IDetailCategoryBuilder& SceneUnderstandingCategory = DetailLayout.EditCategory(TEXT("Scene Understanding"));
	IDetailCategoryBuilder& DisplayRefreshRateCategory = DetailLayout.EditCategory(TEXT("Display Refresh Rate"));

	FacialTrackingCategory.AddCustomRow(LOCTEXT("FacialTrackingUsageInfo", "Facial Tracking Info"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 10, 10, 10))
				.FillWidth(1.0f)
				[
					SNew(SRichTextBlock)
					.Text(LOCTEXT("FacialTrackingUsageInfoMessage",
						"<RichTextBlock.TextHighlight>WARNING:</> Unsupported devices: Vive Cosmos."))
					.TextStyle(FAppStyle::Get(), "MessageLog")
					.DecoratorStyleSet(&FAppStyle::Get())
					.AutoWrapText(true)
				]
			]
		];

	WristTrackerCategory.AddCustomRow(LOCTEXT("WristTrackerUsageInfo", "Wrist Tracker Info"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.Padding(FMargin(10, 10, 10, 10))
		.FillWidth(1.0f)
		[
			SNew(SRichTextBlock)
			.Text(LOCTEXT("WristTrackerUsageInfoMessage",
				"<RichTextBlock.TextHighlight>WARNING:</> Unsupported devices: Vive Cosmos & Vive Pro series."))
		.TextStyle(FAppStyle::Get(), "MessageLog")
		.DecoratorStyleSet(&FAppStyle::Get())
		.AutoWrapText(true)
		]
		]
		];

	SceneUnderstandingCategory.AddCustomRow(LOCTEXT("SceneUnderstandingUsageInfo", "Scene Understanding Info"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 10, 10, 10))
				.FillWidth(1.0f)
				[
					SNew(SRichTextBlock)
					.Text(LOCTEXT("SceneUnderstandingUsageInfoMessage",
						"<RichTextBlock.TextHighlight>WARNING:</> Unsupported devices: All Vive AIO devices."))
					.TextStyle(FAppStyle::Get(), "MessageLog")
					.DecoratorStyleSet(&FAppStyle::Get())
					.AutoWrapText(true)
				]
			]
		];

	DisplayRefreshRateCategory.AddCustomRow(LOCTEXT("DisplayRefreshRateUsageInfo", "Display Refresh Rate Info"), false)
		.WholeRowWidget
		[
			SNew(SBorder)
			.Padding(1)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 10, 10, 10))
				.FillWidth(1.0f)
				[
					SNew(SRichTextBlock)
					.Text(LOCTEXT("DisplayRefreshRateUsageInfoMessage",
						"<RichTextBlock.TextHighlight>WARNING:</> Unsupported devices: Vive Cosmos & Vive Pro series."))
					.TextStyle(FAppStyle::Get(), "MessageLog")
					.DecoratorStyleSet(&FAppStyle::Get())
					.AutoWrapText(true)
				]
			]
		];
}

FViveOpenXRSettingsCustomization::FViveOpenXRSettingsCustomization()
{
}
