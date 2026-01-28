// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "GameplayTagContainer.h"
#include "BHInputConfig.generated.h"

/**
 * Structure to map InputAction to GameplayTag
 */
USTRUCT(BlueprintType)
struct FBHInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Input configuration data asset that maps InputActions to GameplayTags
 * Used for ability input binding following Lyra pattern
 */
UCLASS()
class PROJECTBOH_API UBHInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UBHInputConfig(const FObjectInitializer& ObjectInitializer);

	/** Array of InputActions mapped to their corresponding InputTags */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FBHInputAction> AbilityInputActions;
};
