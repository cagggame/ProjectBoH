// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BHAbilitySystemComponent.h"

void UBHAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	// Iterate through all activatable abilities
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// Check if the ability's DynamicAbilityTags contains the input tag
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			// Try to activate the ability
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UBHAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	
}

