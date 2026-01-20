// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "BHBaseAttributeComponent.generated.h"

class UBHAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHBaseAttributeComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UBHBaseAttributeComponent(const FObjectInitializer& ObjectInitializer);

	void InitBaseAttributeComponent(UBHAbilitySystemComponent* InASC);
	
protected:
	TWeakObjectPtr<UBHAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<const class UBHBaseAttributeSet> BaseAttributeSet;
};
