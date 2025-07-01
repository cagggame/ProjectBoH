// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "BohButtonBase.generated.h"

class UCommonLazyImage;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class PROJECTBOH_API UBohButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(const FText& InText);

protected:
	// UUserWidget interface
	virtual void NativePreConstruct() override;
	// End UUserWidget interface

	// UCommonButtonBase interface
	virtual void UpdateInputActionWidget() override;
	virtual void OnInputMethodChanged(ECommonInputType CurrentInputType) override;
	// End UCommonButtonBase interface

	void RefreshButtonText();

	void RefreshButtonIcon();

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateButtonStyle();

private:
	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	uint8 bOverride_ButtonText : 1;

	UPROPERTY(EditAnywhere, Category="Button", meta=(EditCondition="bOverride_ButtonText"))
	FText ButtonText;

	UPROPERTY(EditAnywhere, Category="Button", meta=(InlineEditConditionToggle))
	uint8 bEnableIcon : 1;

	UPROPERTY(EditAnywhere, Category="Button", meta=(EditCondition="bEnableIcon"))
	FSlateBrush IconBrush;

	UPROPERTY(meta=(BindWidgetOptional))
	TObjectPtr<UCommonLazyImage> LazyImage_Icon;
};
