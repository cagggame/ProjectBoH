// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SubtitleDisplayOptions.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SubtitleDisplaySubsystem.generated.h"

USTRUCT()
struct FSubtitleFormat
{
	GENERATED_BODY()

public:
	FSubtitleFormat()
		: SubtitleTextSize(ESubtitleDisplayTextSize::Medium)
		, SubtitleTextColor(ESubtitleDisplayTextColor::White)
		, SubtitleTextBorder(ESubtitleDisplayTextBorder::None)
		, SubtitleBackgroundOpacity(ESubtitleDisplayBackgroundOpacity::Medium)
	{
	}

public:
	UPROPERTY(EditAnywhere, Category="Display Info")
	ESubtitleDisplayTextSize SubtitleTextSize;

	UPROPERTY(EditAnywhere, Category="Display Info")
	ESubtitleDisplayTextColor SubtitleTextColor;

	UPROPERTY(EditAnywhere, Category="Display Info")
	ESubtitleDisplayTextBorder SubtitleTextBorder;

	UPROPERTY(EditAnywhere, Category="Display Info")
	ESubtitleDisplayBackgroundOpacity SubtitleBackgroundOpacity;
};

UCLASS(DisplayName="Subtitle Display")
class GAMESUBTITLES_API USubtitleDisplaySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	DECLARE_EVENT_OneParam(USubtitleDisplaySubsystem, FDisplayFormatChangedEvent, const FSubtitleFormat& /*DisplayFormat*/);
	FDisplayFormatChangedEvent DisplayFormatChangedEvent;

public:
	static USubtitleDisplaySubsystem* Get(const ULocalPlayer* LocalPlayer);

public:
	USubtitleDisplaySubsystem();

	// USubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// End of USubsystem interface

	void SetSubtitleDisplayOptions(const FSubtitleFormat& InOptions);
	const FSubtitleFormat& GetSubtitleDisplayOptions() const;

private:
	UPROPERTY()
	FSubtitleFormat SubtitleFormat;
};
