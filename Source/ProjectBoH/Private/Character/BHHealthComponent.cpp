// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BHHealthComponent.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/BHHealthAttributeSet.h"

UBHHealthComponent::UBHHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Disable tick
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UBHHealthComponent::InitHealthComponent(UBHAbilitySystemComponent* InASC)
{
	if (AbilitySystemComponent.IsValid() or !InASC)
	{
		return;
	}

	AbilitySystemComponent = InASC;
	HealthAttributeSet = InASC->GetSet<UBHHealthAttributeSet>();
	if (!HealthAttributeSet.IsValid())
	{
		return;
	}
}
