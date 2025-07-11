// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubtitleDisplaySubsystem.h"
#include "Components/Widget.h"
#include "SubtitleDisplay.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta=(DisableNativeTick))
class GAMESUBTITLES_API USubtitleDisplay : public UWidget
{
	GENERATED_UCLASS_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Display Info")
	FSubtitleFormat Format;

	UPROPERTY(EditAnywhere, Category="Display Info")
	TObjectPtr<USubtitleDisplayOptions> Options;

	// Whether text wraps onto a new line when it's length exceeds this width; if this value is zero or negative, no wrapping occurs.
	UPROPERTY(EditAnywhere, Category="Display Info")
	float WrapTextAt;

	/** Preview text to be displayed when designing the widget */
	UPROPERTY(EditAnywhere, Category="Preview")
	bool bPreviewMode;

	/** Preview text to be displayed when designing the widget */
	UPROPERTY(EditAnywhere, Category="Preview")
	FText PreviewText;

public:
	// UWidget Interface
	virtual void SynchronizeProperties() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
#if WITH_EDITOR
	virtual void ValidateCompiledDefaults(IWidgetCompilerLog& CompileLog) const override;
#endif
	// End UWidget Interface

	UFUNCTION(BlueprintCallable, Category="Subtitles", meta=(Tooltip="True if there are subtitles currently.  False if the subtitle text is empty."))
	bool HasSubtitles();

protected:
	// UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// End UWidget Interface

	void HandleSubtitleDisplayOptionChanged(const FSubtitleFormat& InDisplayFormat);

private:
	void RebuildStyle();

private:
	UPROPERTY(Transient)
	FTextBlockStyle GeneratedStyle;

	UPROPERTY(Transient)
	FSlateBrush GeneratedBackgroundBorder;

	/** The actual widget for displaying subtitle data */
	TSharedPtr<class SSubtitleDisplay> SubtitleWidget;
};
