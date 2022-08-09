
#pragma once

#include "CoreMinimal.h"
#include "CoreTypes.generated.h"

class ABaseWeapon;

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Ammo")
	int32 TotalBullets;

	UPROPERTY(EditDefaultsOnly, Category="Ammo")
	int32 ClipBullets;

	FAmmoData()
	{
		TotalBullets = 120;
		ClipBullets = 30;
	}
	
};

USTRUCT()
struct FWeaponItemData
{
	GENERATED_BODY()

	FWeaponItemData() : FWeaponItemData(-1, nullptr){}
	FWeaponItemData(int32 IdNum, UClass* ObjClass)
	{
		Class = ObjClass;
		Id = IdNum;
	}
	bool IsEmpty() const
	{
		return Id<0;
	}
	FORCEINLINE int32 GetID() const {return Id;}
	FORCEINLINE UClass* GetWeaponClass() const {return Class;}
private:
	UPROPERTY()
	int32 Id;
	UPROPERTY()
	UClass* Class;
};

USTRUCT()
struct FWeaponSaveData
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FWeaponItemData ItemData;

	UPROPERTY()
	FAmmoData AmmoData;
public:
	FWeaponSaveData() : FWeaponSaveData(FWeaponItemData(), FAmmoData()) {}
	FWeaponSaveData(const FWeaponItemData& ItemD, const FAmmoData& AmmoD)
	{
		ItemData = ItemD;
		AmmoData = AmmoD;
	}

	FORCEINLINE const FWeaponItemData& GetItemData()const {return ItemData;}
	FORCEINLINE const FAmmoData& GetAmmoData()const {return AmmoData;}
};