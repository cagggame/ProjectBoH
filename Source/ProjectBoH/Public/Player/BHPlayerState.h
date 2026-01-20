// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BHPlayerState.generated.h"

class UBHBaseAttributeSet;
class UBHAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTBOH_API ABHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABHPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBHBaseAttributeSet* GetBaseAttributeSet() const;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBHAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UBHBaseAttributeSet> BaseAttributeSet;
};
