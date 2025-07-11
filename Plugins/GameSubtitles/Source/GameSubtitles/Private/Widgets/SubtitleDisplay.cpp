// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SubtitleDisplay.h"

#include "Editor/WidgetCompilerLog.h"
#include "Widgets/SSubtitleDisplay.h"

#define LOCTEXT_NAMESPACE "SubtitleDisplay"

USubtitleDisplay::USubtitleDisplay(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, WrapTextAt(0) // No wrapping by default
{
}

void USubtitleDisplay::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	RebuildStyle();

	if (IsDesignTime() || bPreviewMode)
	{
		SubtitleWidget->SetCurrentSubtitleText(PreviewText);
	}
}

void USubtitleDisplay::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	SubtitleWidget.Reset();
	if (USubtitleDisplaySubsystem* SubtitleDisplaySubsystem = UGameInstance::GetSubsystem<USubtitleDisplaySubsystem>(GetGameInstance()))
	{
		SubtitleDisplaySubsystem->DisplayFormatChangedEvent.RemoveAll(this);
	}
}

#if WITH_EDITOR

void USubtitleDisplay::ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const
{
	Super::ValidateCompiledDefaults(CompileLog);

	if (!Options)
	{
		CompileLog.Error(FText::Format(LOCTEXT("Error_USubtitleDisplay_MissingOptions", "{0} has no subtitle Options asset specified."), FText::FromString(GetName())));
	}
}

#endif

bool USubtitleDisplay::HasSubtitles()
{
	return SubtitleWidget.IsValid() && SubtitleWidget->HasSubtitles();
}

TSharedRef<SWidget> USubtitleDisplay::RebuildWidget()
{
	if (USubtitleDisplaySubsystem* SubtitleDisplaySubsystem = UGameInstance::GetSubsystem<USubtitleDisplaySubsystem>(GetGameInstance()))
	{
		SubtitleDisplaySubsystem->DisplayFormatChangedEvent.AddUObject(this, &ThisClass::HandleSubtitleDisplayOptionChanged);
		Format = SubtitleDisplaySubsystem->GetSubtitleDisplayOptions();
	}

	SubtitleWidget = SNew(SSubtitleDisplay)
		.TextStyle(&GeneratedStyle)
		.WrapTextAt(WrapTextAt)
		.ManualSubtitles(IsDesignTime() || bPreviewMode);

	RebuildStyle();

	return SubtitleWidget.ToSharedRef();
}

void USubtitleDisplay::HandleSubtitleDisplayOptionChanged(const FSubtitleFormat& InDisplayFormat)
{
	if (SubtitleWidget.IsValid())
	{
		Format = InDisplayFormat;
		RebuildStyle();
	}
}

void USubtitleDisplay::RebuildStyle()
{
	GeneratedStyle = FTextBlockStyle();

	if (Options)
	{
		GeneratedStyle.SetFont(Options->Font);
		GeneratedStyle.SetFontSize(Options->DisplayTextSizes[(int32)Format.SubtitleTextSize]);
		GeneratedStyle.SetColorAndOpacity(Options->DisplayTextColors[(int32)Format.SubtitleTextColor]);

		switch (Format.SubtitleTextBorder)
		{
		case ESubtitleDisplayTextBorder::DropShadow:
			{
				const float ShadowSize = FMath::Max(1.f, Options->DisplayBorderSize[(int32)Format.SubtitleTextBorder] / 2.f);
				GeneratedStyle.SetShadowOffset(FVector2D(ShadowSize, ShadowSize));
				break;
			}
		case ESubtitleDisplayTextBorder::Outline:
			{
				const float OutlineSize = FMath::Max(1.f, Options->DisplayBorderSize[(int32)ESubtitleDisplayTextBorder::Outline] * (float)Format.SubtitleTextSize);
				GeneratedStyle.Font.OutlineSettings.OutlineSize = OutlineSize;
				break;
			}
		case ESubtitleDisplayTextBorder::None:
		default:
			break;
		}

		FLinearColor CurrentBackgroundColor = Options->BackgroundBrush.TintColor.GetSpecifiedColor();
		CurrentBackgroundColor.A = Options->DisplayBackgroundOpacity[(int32)Format.SubtitleBackgroundOpacity];
		GeneratedBackgroundBorder = Options->BackgroundBrush;
		GeneratedBackgroundBorder.TintColor = CurrentBackgroundColor;

		if (SubtitleWidget.IsValid())
		{
			SubtitleWidget->SetTextStyle(GeneratedStyle);
			SubtitleWidget->SetBackgroundBrush(&GeneratedBackgroundBorder);
		}
	}
}

#undef LOCTEXT_NAMESPACE