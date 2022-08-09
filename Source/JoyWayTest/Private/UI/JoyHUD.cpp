
#include "UI/JoyHUD.h"
#include "UI/PlayerGameWidget.h"
#include "UI/WeaponInventoryWidget.h"

void AJoyHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (PlayerWidgetClass)
	{
		PlayerWidget = CreateWidget<UPlayerGameWidget>(GetWorld(), PlayerWidgetClass,
			"PlayerWidget");
		PlayerWidget->AddToViewport();
	}

	if (InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UWeaponInventoryWidget>(GetWorld(), InventoryWidgetClass,
			"InventoryWidget");
		InventoryWidget->AddToViewport();
		InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

TDelegate<void(float)> AJoyHUD::GetHealthDelegate()
{
	
	TDelegate<void(float)> HealthDelegate;
	const auto HealthBar = PlayerWidget->GetHealthBar();
	HealthDelegate.BindUObject(HealthBar, &UProgressBar::SetPercent);
	return HealthDelegate;
}

const TDelegate<void(int32, int32)>& AJoyHUD::GetWeaponDelegate() const
{
	return PlayerWidget->GetWeaponWidget()->GetAmmoDelegate();
}

void AJoyHUD::ToggleInventory(bool bNewVisibility)
{
	PlayerWidget->SetVisibility(bNewVisibility ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
	InventoryWidget->SetVisibility(!bNewVisibility ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void AJoyHUD::AddItemToInventory(const TDelegate<void()>& CallbackDelegate)
{
	InventoryWidget->AddItem(CallbackDelegate);
}
