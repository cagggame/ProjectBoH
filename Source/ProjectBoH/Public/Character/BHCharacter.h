// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "BHCharacter.generated.h"

USTRUCT(BlueprintType)
struct FBHCharacterAbilitySet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBHGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;
};

UCLASS()
class PROJECTBOH_API ABHCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABHCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	TWeakObjectPtr<class UBHAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UBHBaseAttributeSet> BaseAttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<FBHCharacterAbilitySet> CharacterAbilitySet;
};
