// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BHPlayerState.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/BHBaseAttributeSet.h"

ABHPlayerState::ABHPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBHAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	BaseAttributeSet = CreateDefaultSubobject<UBHBaseAttributeSet>(TEXT("BaseAttributeSet"));

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* ABHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBHBaseAttributeSet* ABHPlayerState::GetBaseAttributeSet() const
{
	return BaseAttributeSet;
}
