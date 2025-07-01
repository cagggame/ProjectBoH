// Fill out your copyright notice in the Description page of Project Settings.


#include "BohButtonBase.h"

#include "CommonActionWidget.h"
#include "CommonLazyImage.h"

void UBohButtonBase::SetButtonText(const FText& InText)
{
	bOverride_ButtonText = InText.IsEmpty();
	ButtonText = InText;
	RefreshButtonText();
}

void UBohButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateButtonStyle();
	RefreshButtonText();
	RefreshButtonIcon();
}

void UBohButtonBase::UpdateInputActionWidget()
{
	Super::UpdateInputActionWidget();

	UpdateButtonStyle();
	RefreshButtonText();
	RefreshButtonIcon();
}

void UBohButtonBase::OnInputMethodChanged(ECommonInputType CurrentInputType)
{
	Super::OnInputMethodChanged(CurrentInputType);

	UpdateButtonStyle();
}

void UBohButtonBase::RefreshButtonText()
{
	if (bOverride_ButtonText || ButtonText.IsEmpty())
	{
		if (InputActionWidget)
		{
			const FText ActionDisplayText = InputActionWidget->GetDisplayText();
			if (!ActionDisplayText.IsEmpty())
			{
				UpdateButtonText(ActionDisplayText);
			}
		}
	}

	UpdateButtonText(ButtonText);
}

void UBohButtonBase::RefreshButtonIcon()
{
	if (bEnableIcon && LazyImage_Icon)
	{
		LazyImage_Icon->SetBrush(IconBrush);
	}
}
