// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "BHAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** Called when an input tag is pressed. Finds and activates abilities matching the input tag. */
	void AbilityInputTagPressed(const FGameplayTag& InputTag);

	/** Called when an input tag is released. Handles abilities that need release events. */
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
};
