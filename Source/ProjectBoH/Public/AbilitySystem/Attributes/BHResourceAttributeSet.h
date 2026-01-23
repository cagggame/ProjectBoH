// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/BHAttributeSet.h"
#include "BHResourceAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHResourceAttributeSet : public UBHAttributeSet
{
	GENERATED_BODY()

public:
	UBHResourceAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 定义属性访问器
	ATTRIBUTE_ACCESSORS(UBHResourceAttributeSet, Mana);
	ATTRIBUTE_ACCESSORS(UBHResourceAttributeSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UBHResourceAttributeSet, ManaRegen);

protected:
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana);

	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen);

private:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ManaRegen, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData ManaRegen;
};
