// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BHBaseAttributeComponent.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/BHBaseAttributeSet.h"

UBHBaseAttributeComponent::UBHBaseAttributeComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Disable tick
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UBHBaseAttributeComponent::InitBaseAttributeComponent(UBHAbilitySystemComponent* InASC)
{
	if (AbilitySystemComponent.IsValid() or !InASC)
	{
		return;
	}

	AbilitySystemComponent = InASC;
	BaseAttributeSet = InASC->GetSet<UBHBaseAttributeSet>();
	if (!BaseAttributeSet.IsValid())
	{
		return;
	}
}
