// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/BHBaseAttributeSet.h"

#include "Net/UnrealNetwork.h"

UBHBaseAttributeSet::UBHBaseAttributeSet()
{
}

void UBHBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, Health, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, BasicDefense, COND_None, REPNOTIFY_Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UBHBaseAttributeSet, AbilityDefense, COND_None, REPNOTIFY_Always)
}

void UBHBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHBaseAttributeSet, Health, OldHealth);
}

void UBHBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBHBaseAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHBaseAttributeSet, HealthRegen, OldHealthRegen);
}

void UBHBaseAttributeSet::OnRep_BasicDefense(const FGameplayAttributeData& OldBasicDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHBaseAttributeSet, BasicDefense, OldBasicDefense);
}

void UBHBaseAttributeSet::OnRep_AbilityDefense(const FGameplayAttributeData& OldAbilityDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHBaseAttributeSet, AbilityDefense, OldAbilityDefense);
}
