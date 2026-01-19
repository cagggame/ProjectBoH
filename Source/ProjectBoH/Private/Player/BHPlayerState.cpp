// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BHPlayerState.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/BHAttributeSet.h"

ABHPlayerState::ABHPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBHAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UBHAttributeSet>(TEXT("AttributeSet"));

	SetNetUpdateFrequency(100.f);
}

UAbilitySystemComponent* ABHPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBHAttributeSet* ABHPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
