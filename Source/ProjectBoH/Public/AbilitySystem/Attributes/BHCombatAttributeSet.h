// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attributes/BHAttributeSet.h"
#include "BHCombatAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBOH_API UBHCombatAttributeSet : public UBHAttributeSet
{
	GENERATED_BODY()

	public:
    UBHCombatAttributeSet();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // --- 核心战斗属性 ---
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, Power);              // 强度 (影响普攻和技能)
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, AttackSpeed);        // 攻速
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, BasicPenetration);   // 基础穿透 (抵消 BasicDefense)
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, AbilityPenetration); // 技能穿透 (抵消 AbilityDefense)

    // --- Yin 专属机制属性 ---
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, CleavePercentage);   // 分裂比例 (0.0~1.0)
    ATTRIBUTE_ACCESSORS(UBHCombatAttributeSet, AttackRange);        // 攻击距离 (普攻射线检测长度)

protected:
    UFUNCTION()
    void OnRep_Power(const FGameplayAttributeData& OldPower);

    UFUNCTION()
    void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed);

    UFUNCTION()
    void OnRep_BasicPenetration(const FGameplayAttributeData& OldBasicPenetration);

    UFUNCTION()
    void OnRep_AbilityPenetration(const FGameplayAttributeData& OldAbilityPenetration);

    UFUNCTION()
    void OnRep_CleavePercentage(const FGameplayAttributeData& OldCleavePercentage);

    UFUNCTION()
    void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange);

private:
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Power, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData Power;

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackSpeed, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData AttackSpeed;

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_BasicPenetration, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData BasicPenetration;

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AbilityPenetration, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData AbilityPenetration;
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CleavePercentage, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData CleavePercentage;
    
    UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_AttackRange, meta=(AllowPrivateAccess=true))
    FGameplayAttributeData AttackRange;
};
