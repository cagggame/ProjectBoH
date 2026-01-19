// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BHCharacter.h"

#include "Player/BHPlayerState.h"

// Sets default values
ABHCharacter::ABHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABHCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
