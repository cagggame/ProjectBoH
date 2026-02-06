// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BHGameplayAbility.h"
#include "BHAbility_PrimaryAttack.generated.h"

class UAnimMontage;
class UAbilityTask_PlayMontageAndWait;

/**
 * 
 */
UCLASS(Abstract)
class PROJECTBOH_API UBHAbility_PrimaryAttack : public UBHGameplayAbility
{
	GENERATED_BODY()

public:
	UBHAbility_PrimaryAttack();

	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo) override;

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	/** Override to provide section names (default: Attack1, Attack2, ...). */
	UFUNCTION(BlueprintNativeEvent, Category = "BH|PrimaryAttack")
	FName GetSectionNameForIndex(int32 ComboIndex) const;
	virtual FName GetSectionNameForIndex_Implementation(int32 ComboIndex) const;

	/** Called when a combo section hits (e.g. from anim notify). Override or use GE to apply damage. */
	UFUNCTION(BlueprintNativeEvent, Category = "BH|PrimaryAttack")
	void OnComboHit(int32 ComboIndex);
	virtual void OnComboHit_Implementation(int32 ComboIndex);

	/** Montage to play; sections should match GetSectionNameForIndex (Attack1..AttackN). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BH|PrimaryAttack")
	TSoftObjectPtr<UAnimMontage> SoftAttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BH|PrimaryAttack", Meta = (ClampMin = "1", ClampMax = "16"))
	uint8 MaxComboCount = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BH|PrimaryAttack", Meta = (ClampMin = "0.0"))
	float ComboResetTime = 0.5f;

private:
	void PlayNextComboSection(
	);

	UFUNCTION()
	void OnMontageCompleted();
	UFUNCTION()
	void OnMontageCancelled();

	/** Current 1-based combo step (1..MaxComboCount). */
	uint8 CurrentComboIndex = 0;

	/** Time when current combo chain started (first press or last section start). */
	float LastComboTime = 0.f;

	/** True when player pressed attack again during the current section. */
	bool bWantsNextCombo = false;

	TWeakObjectPtr<UAbilityTask_PlayMontageAndWait> MontageTask;
};
