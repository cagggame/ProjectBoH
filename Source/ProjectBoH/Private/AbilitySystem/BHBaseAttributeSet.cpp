// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BHBaseAttributeSet.h"

#include "Net/UnrealNetwork.h"

UBHBaseAttributeSet::UBHBaseAttributeSet()
{
}

void UBHBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
}

void UBHBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
}

void UBHBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
}
