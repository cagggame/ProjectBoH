// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class GAMESUBTITLES_API SSubtitleDisplay : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSubtitleDisplay)
		: _TextStyle(&FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText"))
	{}
		SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)
		SLATE_ATTRIBUTE(float, WrapTextAt)
		SLATE_ATTRIBUTE(bool, ManualSubtitles)
	SLATE_END_ARGS()

	~SSubtitleDisplay();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	void SetTextStyle(const FTextBlockStyle& InTextStyle);

	void SetBackgroundBrush(const FSlateBrush* InSlateBrush);

	void SetCurrentSubtitleText(const FText& InSubtitleText);

	bool HasSubtitles() const;

	void SetWrapTextAt(const TAttribute<float>& InWrapTextAt);

private:
	void HandleSubtitleChanged(const FText& SubtitleText);

private:
	TSharedPtr<class SBorder> Background;

	// Actual widget that will display the subtitle text.
	TSharedPtr<class SRichTextBlock> TextDisplay;
};
