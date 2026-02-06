// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "BHGameplayAbility.generated.h"

class UBHAbilitySystemComponent;
class ABHCharacter;
class ABHHeroCharacter;
class ABHPlayerController;

/**
 * EBHAbilityActivationPolicy
 *
 * Defines how an ability is meant to activate.
 * Simplified version inspired by Lyra, tuned for ARPG skills.
 */
UENUM(BlueprintType)
enum class EBHAbilityActivationPolicy : uint8
{
	// Try to activate the ability when the input is triggered.
	OnInputTriggered UMETA(DisplayName = "On Input Triggered"),

	// Continually try to activate the ability while the input is active.
	WhileInputActive UMETA(DisplayName = "While Input Active"),

	// Try to activate the ability when an avatar is assigned / on spawn.
	OnSpawn UMETA(DisplayName = "On Spawn")
};

/**
 * EBHAbilityActivationGroup
 *
 * Defines how an ability activates in relation to other abilities.
 * Group conflict resolution can be implemented in UBHAbilitySystemComponent.
 */
UENUM(BlueprintType)
enum class EBHAbilityActivationGroup : uint8
{
	// Ability runs independently of all other abilities.
	Independent UMETA(DisplayName = "Independent"),

	// Ability is canceled and replaced by other exclusive abilities.
	Exclusive_Replaceable UMETA(DisplayName = "Exclusive Replaceable"),

	// Ability blocks all other exclusive abilities from activating.
	Exclusive_Blocking UMETA(DisplayName = "Exclusive Blocking"),

	MAX UMETA(Hidden)
};

/**
 * UBHGameplayAbility
 *
 * Base gameplay ability class for this project.
 * Provides:
 * - Activation policy & group
 * - Convenience accessors for ASC / character / controller
 * - Hook for OnSpawn-style passive abilities
 * - Lightweight failure messaging map (tags -> localized text)
 */
UCLASS(Abstract)
class PROJECTBOH_API UBHGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBHGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Returns the BH ASC from the current actor info, if any. */
	UFUNCTION(BlueprintCallable, Category = "BH|Ability")
	UBHAbilitySystemComponent* GetBHAbilitySystemComponentFromActorInfo() const;

	/** Returns the BH base character from the current actor info, if any. */
	UFUNCTION(BlueprintCallable, Category = "BH|Ability")
	ABHCharacter* GetBHCharacterFromActorInfo() const;

	/** Returns the BH hero character from the current actor info, if any. */
	UFUNCTION(BlueprintCallable, Category = "BH|Ability")
	ABHHeroCharacter* GetBHHeroFromActorInfo() const;

	/** Returns the controller associated with this ability's avatar, if any. */
	UFUNCTION(BlueprintCallable, Category = "BH|Ability")
	ABHPlayerController* GetBHPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "BH|Ability")
	AController* GetControllerFromActorInfo() const;

	/** Activation policy configured for this ability. */
	EBHAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

	/** Activation group configured for this ability. */
	EBHAbilityActivationGroup GetActivationGroup() const { return ActivationGroup; }

	/** For OnSpawn abilities: attempt to activate when the pawn/avatar is ready. */
	void TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const;

protected:
	//~UGameplayAbility interface
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
		FGameplayTagContainer* OptionalRelevantTags) const override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
 
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) const override;

	// Called when the ability system is initialized with a pawn avatar.
	virtual void OnPawnAvatarSet();

	/** Called when this ability is granted to the ability system component (Blueprint hook). */
	UFUNCTION(BlueprintImplementableEvent, Category = "BH|Ability", DisplayName = "OnAbilityAdded")
	void K2_OnAbilityAdded();

	/** Called when this ability is removed from the ability system component (Blueprint hook). */
	UFUNCTION(BlueprintImplementableEvent, Category = "BH|Ability", DisplayName = "OnAbilityRemoved")
	void K2_OnAbilityRemoved();

	/** Called when the pawn avatar is set for this ability (Blueprint hook). */
	UFUNCTION(BlueprintImplementableEvent, Category = "BH|Ability", DisplayName = "OnPawnAvatarSet")
	void K2_OnPawnAvatarSet();

protected:
	/** How this ability is meant to activate (input/on spawn, etc.). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BH|Ability Activation")
	EBHAbilityActivationPolicy ActivationPolicy = EBHAbilityActivationPolicy::OnInputTriggered;

	/** Relationship between this ability activating and other abilities activating. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BH|Ability Activation")
	EBHAbilityActivationGroup ActivationGroup = EBHAbilityActivationGroup::Independent;

	/** Simple map of failure tags to user-facing messages (for UI / logs). */
	UPROPERTY(EditDefaultsOnly, Category = "BH|Ability Failure")
	TMap<FGameplayTag, FText> FailureTagToUserFacingMessages;
};

