// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities/BHAbility_PrimaryAttack.h"

#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"

UBHAbility_PrimaryAttack::UBHAbility_PrimaryAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationPolicy = EBHAbilityActivationPolicy::OnInputTriggered;
	ActivationGroup = EBHAbilityActivationGroup::Exclusive_Replaceable;
}

void UBHAbility_PrimaryAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	// Buffer next combo when player presses attack again during current section
	bWantsNextCombo = true;
}

void UBHAbility_PrimaryAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!SoftAttackMontage || MaxComboCount == 0)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}

	UWorld* World = GetWorld();
	const float TimeNow = World ? World->GetTimeSeconds() : 0.f;

	// Reset combo if too much time passed since last action
	if (TimeNow - LastComboTime > ComboResetTime)
	{
		CurrentComboIndex = 0;
	}

	CurrentComboIndex = (CurrentComboIndex % MaxComboCount) + 1;
	LastComboTime = TimeNow;
	bWantsNextCombo = false;

	PlayNextComboSection();
}

void UBHAbility_PrimaryAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	MontageTask.Reset();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FName UBHAbility_PrimaryAttack::GetSectionNameForIndex_Implementation(int32 ComboIndex) const
{
	return FName(FString::Printf(TEXT("Combo%d"), ComboIndex));
}

void UBHAbility_PrimaryAttack::OnComboHit_Implementation(int32 ComboIndex)
{
	// Override in subclass or Blueprint to apply damage (e.g. via GE or trace).
}

void UBHAbility_PrimaryAttack::PlayNextComboSection()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	AActor* Avatar = GetAvatarActorFromActorInfo();
	if (!ASC || !Avatar)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	UAnimMontage* Montage = Cast<UAnimMontage>(UKismetSystemLibrary::LoadAsset_Blocking(SoftAttackMontage));
	const FName SectionName = GetSectionNameForIndex(CurrentComboIndex);

	UAbilityTask_PlayMontageAndWait* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
		this,
		FName(TEXT("PlayPrimaryAttackAnim")),
		Montage,
		1.0f,
		SectionName,
		true,
		1.0f
	);

	if (!Task)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	Task->OnBlendOut.AddDynamic(this, &UBHAbility_PrimaryAttack::OnMontageCompleted);
	Task->OnCancelled.AddDynamic(this, &UBHAbility_PrimaryAttack::OnMontageCancelled);
	Task->OnInterrupted.AddDynamic(this, &UBHAbility_PrimaryAttack::OnMontageCancelled);

	MontageTask = Task;
	Task->ReadyForActivation();
}

void UBHAbility_PrimaryAttack::OnMontageCompleted()
{
	if (bWantsNextCombo && CurrentComboIndex < MaxComboCount)
	{
		bWantsNextCombo = false;
		PlayNextComboSection();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}

void UBHAbility_PrimaryAttack::OnMontageCancelled()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
