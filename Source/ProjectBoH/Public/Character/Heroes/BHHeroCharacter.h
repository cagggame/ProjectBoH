// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BHCharacter.h"
#include "BHHeroCharacter.generated.h"

class UBHBaseAttributeSet;
/**
 * 
 */
UCLASS()
class PROJECTBOH_API ABHHeroCharacter : public ABHCharacter
{
	GENERATED_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

protected:
	
};
