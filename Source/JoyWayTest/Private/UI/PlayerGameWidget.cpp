// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerGameWidget.h"

void UPlayerGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (WeaponWidgetClass) WeaponWidget = CreateWidget<UWeaponWidget>(GetWorld()->GetGameInstance(),
		WeaponWidgetClass, "WeaponWidget");

	if (WeaponWidget) WeaponWidget->AddToViewport();
	
}

void UPlayerGameWidget::SetVisibility(ESlateVisibility InVisibility)
{
	Super::SetVisibility(InVisibility);

	WeaponWidget->SetVisibility(InVisibility);
}
