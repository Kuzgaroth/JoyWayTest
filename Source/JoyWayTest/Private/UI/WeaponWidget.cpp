

#include "UI/WeaponWidget.h"

const TDelegate<void(int32, int32)>& UWeaponWidget::GetAmmoDelegate()
{
	return AmmoDelegate = TDelegate<void(int32, int32)>::CreateUObject(this, &UWeaponWidget::SetAmmoData);
}

void UWeaponWidget::SetAmmoData(int32 ClipAmmo, int32 TotalAmmo) const
{
	ClipAmmoForm->SetText(FText::AsNumber(ClipAmmo));
	TotalAmmoForm->SetText(FText::AsNumber(TotalAmmo));
}
