// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Heroes/BHHeroCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AbilitySystem/BHAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/BHBaseAttributeSet.h"
#include "Player/BHPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/BHInputConfig.h"
#include "GameplayTagContainer.h"

ABHHeroCharacter::ABHHeroCharacter()
{
	// Create Spring Arm Component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 450.0f; // Camera distance from character

	// Create Camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ABHHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (InputMappingContext)
	{
		APlayerController* PC = GetController<APlayerController>();
		check(PC);
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}

	// Bind ability input actions
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InputConfig)
		{
			// Bind all ability input actions
			for (const FBHInputAction& Action : InputConfig->AbilityInputActions)
			{
				if (Action.InputAction && Action.InputTag.IsValid())
				{
					// Bind pressed event
					EnhancedInputComponent->BindAction(
						Action.InputAction,
						ETriggerEvent::Triggered,
						this,
						&ABHHeroCharacter::Input_AbilityInputTagPressed,
						Action.InputTag
					);

					// Bind released event
					// EnhancedInputComponent->BindAction(
					// 	Action.InputAction,
					// 	ETriggerEvent::Completed,
					// 	this,
					// 	&ABHHeroCharacter::Input_AbilityInputTagReleased,
					// 	Action.InputTag
					// );
				}
			}
		}
	}
}

void ABHHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	ABHPlayerState* PS = GetPlayerState<ABHPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBHAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		
		BaseAttributeSet = PS->GetBaseAttributeSet();
	}
}

void ABHHeroCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	ABHPlayerState* PS = GetPlayerState<ABHPlayerState>();
	if (PS)
	{
		AbilitySystemComponent = Cast<UBHAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
		
		BaseAttributeSet = PS->GetBaseAttributeSet();
	}
}

void ABHHeroCharacter::IA_Move_Triggered(const FVector2D& InputActionValue)
{
	if (AController* LocalController = GetController())
	{
		const FRotator MovementRotation(0.0f, LocalController->GetControlRotation().Yaw, 0.0f);

		if (InputActionValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MovementDirection, InputActionValue.X);
		}

		if (InputActionValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MovementDirection, InputActionValue.Y);
		}
	}	
}

void ABHHeroCharacter::IA_Look_Triggered(const FVector2D& InputActionValue)
{
	if (InputActionValue.X != 0.0f)
	{
		AddControllerYawInput(InputActionValue.X);
	}

	if (InputActionValue.Y != 0.0f)
	{
		AddControllerPitchInput(InputActionValue.Y);
	}	
}

void ABHHeroCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void ABHHeroCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}
