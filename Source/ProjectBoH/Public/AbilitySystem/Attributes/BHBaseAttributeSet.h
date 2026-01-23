// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/BHAttributeSet.h"
#include "BHBaseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHBaseAttributeSet : public UBHAttributeSet
{
	GENERATED_BODY()

public:
	UBHBaseAttributeSet();

	ATTRIBUTE_ACCESSORS(UBHBaseAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UBHBaseAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UBHBaseAttributeSet, BasicDefense);
	ATTRIBUTE_ACCESSORS(UBHBaseAttributeSet, AbilityDefense);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen);

	UFUNCTION()
	void OnRep_BasicDefense(const FGameplayAttributeData& OldBasicDefense);

	UFUNCTION()
	void OnRep_AbilityDefense(const FGameplayAttributeData& OldAbilityDefense);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_HealthRegen, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData HealthRegen;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BasicDefense, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData BasicDefense;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AbilityDefense, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData AbilityDefense;
};
