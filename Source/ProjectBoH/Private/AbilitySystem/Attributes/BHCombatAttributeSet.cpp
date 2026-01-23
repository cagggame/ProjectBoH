// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/BHCombatAttributeSet.h"

#include "Net/UnrealNetwork.h"

UBHCombatAttributeSet::UBHCombatAttributeSet()
{
}

void UBHCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, Power, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, BasicPenetration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, AbilityPenetration, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, CleavePercentage, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UBHCombatAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
}

void UBHCombatAttributeSet::OnRep_Power(const FGameplayAttributeData& OldPower)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, Power, OldPower);
}

void UBHCombatAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, AttackSpeed, OldAttackSpeed);
}

void UBHCombatAttributeSet::OnRep_BasicPenetration(const FGameplayAttributeData& OldBasicPenetration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, BasicPenetration, OldBasicPenetration);
}

void UBHCombatAttributeSet::OnRep_AbilityPenetration(const FGameplayAttributeData& OldAbilityPenetration)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, AbilityPenetration, OldAbilityPenetration);
}

void UBHCombatAttributeSet::OnRep_CleavePercentage(const FGameplayAttributeData& OldCleavePercentage)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, CleavePercentage, OldCleavePercentage);
}

void UBHCombatAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange)
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UBHCombatAttributeSet, AttackRange, OldAttackRange);
}