// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/BHResourceAttributeSet.h"

#include "Net/UnrealNetwork.h"

UBHResourceAttributeSet::UBHResourceAttributeSet()
{
	
}

void UBHResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// 资源类属性通常需要 Always 同步，保证 UI 响应
	DOREPLIFETIME_CONDITION_NOTIFY(UBHResourceAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBHResourceAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBHResourceAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
}

void UBHResourceAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHResourceAttributeSet, Mana, OldMana);
}

void UBHResourceAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHResourceAttributeSet, MaxMana, OldMaxMana);
}

void UBHResourceAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBHResourceAttributeSet, ManaRegen, OldManaRegen);
}