
#include "JoySaveGame.h"

void UJoySaveGame::SetHealth(float Health)
{
	PlayerHealth = Health;
}

void UJoySaveGame::AddWeapon(const FWeaponItemData& ItemData, const FAmmoData& AmmoData)
{
	Weapons.Add(FWeaponSaveData(ItemData, AmmoData));
}
