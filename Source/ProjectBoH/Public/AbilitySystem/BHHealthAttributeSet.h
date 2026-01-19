// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/BHAttributeSet.h"
#include "BHHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHHealthAttributeSet : public UBHAttributeSet
{
	GENERATED_BODY()

public:
	UBHHealthAttributeSet();

protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxHealth;
};
