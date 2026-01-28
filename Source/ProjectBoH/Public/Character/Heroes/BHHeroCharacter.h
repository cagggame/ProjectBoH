// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BHCharacter.h"
#include "Input/BHInputConfig.h"
#include "BHHeroCharacter.generated.h"

class UBHBaseAttributeSet;
/**
 * Hero character with ability input system support
 */
UCLASS()
class PROJECTBOH_API ABHHeroCharacter : public ABHCharacter
{
	GENERATED_BODY()

public:
	ABHHeroCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	UFUNCTION(BlueprintCallable)
	void IA_Move_Triggered(const FVector2D& InputActionValue);
	UFUNCTION(BlueprintCallable)
	void IA_Look_Triggered(const FVector2D& InputActionValue);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	/** Input configuration that maps InputActions to GameplayTags for abilities */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UBHInputConfig> InputConfig;
	
protected:
	/** Called when an ability input tag is pressed */
	void Input_AbilityInputTagPressed(FGameplayTag InputTag);

	/** Called when an ability input tag is released */
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);

	/** Spring arm component for camera positioning */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> SpringArmComponent;

	/** Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;
};
