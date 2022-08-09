
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "JoyWayTest/Public/CoreTypes.h" 
#include "JoySaveGame.generated.h"

UCLASS()
class JOYWAYTEST_API UJoySaveGame : public USaveGame
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float PlayerHealth;
	
	UPROPERTY()
	TArray<FWeaponSaveData> Weapons;
public:
	void SetHealth(float Health);
	FORCEINLINE float GetHealth() const {return  PlayerHealth;}
	void AddWeapon(const FWeaponItemData& ItemData, const FAmmoData& AmmoData);
	FORCEINLINE const TArray<FWeaponSaveData>& GetWeapons() const {return Weapons;}
};
