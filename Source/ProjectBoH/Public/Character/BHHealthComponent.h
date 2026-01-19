// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "BHHealthComponent.generated.h"

class UBHAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:
	UBHHealthComponent(const FObjectInitializer& ObjectInitializer);

	void InitHealthComponent(UBHAbilitySystemComponent* InASC);
	
protected:
	TWeakObjectPtr<UBHAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<const class UBHHealthAttributeSet> HealthAttributeSet;
};
