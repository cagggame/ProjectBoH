// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Heroes/BHHeroCharacter.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/BHBaseAttributeSet.h"
#include "Player/BHPlayerState.h"

void ABHHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABHPlayerState* PS = GetPlayerState<ABHPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBHAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		
		BaseAttributeSet = PS->GetBaseAttributeSet();
	}
}

void ABHHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABHPlayerState* PS = GetPlayerState<ABHPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBHAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		
		BaseAttributeSet = PS->GetBaseAttributeSet();
	}
}
