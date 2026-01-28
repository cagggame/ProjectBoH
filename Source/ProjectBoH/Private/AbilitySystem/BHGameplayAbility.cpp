// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/BHGameplayAbility.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "Character/BHCharacter.h"
#include "Character/Heroes/BHHeroCharacter.h"

#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

UBHGameplayAbility::UBHGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Reasonable defaults for ARPG-style abilities
	ActivationPolicy = EBHAbilityActivationPolicy::OnInputTriggered;
	ActivationGroup = EBHAbilityActivationGroup::Independent;
}

UBHAbilitySystemComponent* UBHGameplayAbility::GetBHASCFromActorInfo() const
{
	return Cast<UBHAbilitySystemComponent>(GetAbilitySystemComponentFromActorInfo());
}

ABHCharacter* UBHGameplayAbility::GetBHCharacterFromActorInfo() const
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	return ActorInfo ? Cast<ABHCharacter>(ActorInfo->AvatarActor.Get()) : nullptr;
}

ABHHeroCharacter* UBHGameplayAbility::GetBHHeroFromActorInfo() const
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	return ActorInfo ? Cast<ABHHeroCharacter>(ActorInfo->AvatarActor.Get()) : nullptr;
}

AController* UBHGameplayAbility::GetControllerFromActorInfo() const
{
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();
	if (!ActorInfo)
	{
		return nullptr;
	}

	if (AController* Controller = ActorInfo->PlayerController.Get())
	{
		return Controller;
	}

	if (APawn* Pawn = Cast<APawn>(ActorInfo->AvatarActor.Get()))
	{
		return Pawn->GetController();
	}

	return nullptr;
}

void UBHGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (ActivationPolicy != EBHAbilityActivationPolicy::OnSpawn)
	{
		return;
	}

	// Respect normal activation conditions.
	FGameplayTagContainer OptionalRelevantTags;
	if (!CanActivateAbility(Spec.Handle, ActorInfo, nullptr, nullptr, &OptionalRelevantTags))
	{
		return;
	}

	// AbilitySystemComponent is non-const, but ActorInfo is passed as const.
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		ASC->TryActivateAbility(Spec.Handle);
	}
}

bool UBHGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	// TODO: Add any global BH-specific checks here (e.g., global stun/lock tags).
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UBHGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	// Blueprint hook.
	K2_OnAbilityAdded();

	// For passive / aura-like abilities that should run on spawn.
	if (ActivationPolicy == EBHAbilityActivationPolicy::OnSpawn)
	{
		TryActivateAbilityOnSpawn(ActorInfo, Spec);
	}
}

void UBHGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);

	// Blueprint hook.
	K2_OnAbilityRemoved();
}

void UBHGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Derived abilities override this to implement their core logic.
}

void UBHGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UBHGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	// Use default GameplayAbility cost checks for now.
	return Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
}

void UBHGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	// Use default GameplayAbility cost application for now.
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
}

void UBHGameplayAbility::OnPawnAvatarSet()
{
	// Native hook; forward to Blueprint if needed.
	K2_OnPawnAvatarSet();
}

