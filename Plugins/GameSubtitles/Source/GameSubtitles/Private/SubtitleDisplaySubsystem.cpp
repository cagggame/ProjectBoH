// Fill out your copyright notice in the Description page of Project Settings.


#include "SubtitleDisplaySubsystem.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(SubtitleDisplaySubsystem)

USubtitleDisplaySubsystem* USubtitleDisplaySubsystem::Get(const ULocalPlayer* LocalPlayer)
{
	return LocalPlayer ? LocalPlayer->GetGameInstance()->GetSubsystem<USubtitleDisplaySubsystem>() : nullptr;
}

USubtitleDisplaySubsystem::USubtitleDisplaySubsystem()
{
}

void USubtitleDisplaySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	
}

void USubtitleDisplaySubsystem::Deinitialize()
{
	
}

void USubtitleDisplaySubsystem::SetSubtitleDisplayOptions(const FSubtitleFormat& InOptions)
{
	SubtitleFormat = InOptions;
	DisplayFormatChangedEvent.Broadcast(SubtitleFormat);
}

const FSubtitleFormat& USubtitleDisplaySubsystem::GetSubtitleDisplayOptions() const
{
	return SubtitleFormat;
}
