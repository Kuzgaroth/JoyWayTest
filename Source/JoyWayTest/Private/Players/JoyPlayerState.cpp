// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/JoyPlayerState.h"

void AJoyPlayerState::UpdateAmmoData(const FAmmoData& NewData, FAmmoData& OldData)
{
	OldData = NewData;
}

void AJoyPlayerState::RegisterNewWeapon(const FWeaponSaveData& NewWeaponData)
{
	WeaponItemDatas.Add(NewWeaponData);
	CallbackDelegate = TDelegate<void()>::CreateUObject(this, &AJoyPlayerState::SelectNewWeapon,
		NewWeaponData.GetItemData().GetID());
	OnWeaponRegistered().Broadcast(CallbackDelegate);
	CurrentWeaponItem = NewWeaponData;
	if (WeaponItemDatas.Num()==1)
	{
		OnWeaponSelectedEvent.Broadcast(CurrentWeaponItem.GetItemData().GetWeaponClass(),
			CurrentWeaponItem.GetAmmoData());
	}
}

void AJoyPlayerState::SelectNewWeapon(int32 Index)
{
	if (CurrentWeaponItem.GetItemData().GetID()==Index) return;
	const auto Result = WeaponItemDatas.FindByPredicate([Index](const FWeaponSaveData& Data)
	{
		return Data.GetItemData().GetID() == Index;
	});
	
	OnWeaponSelectedEvent.Broadcast(Result->GetItemData().GetWeaponClass(), Result->GetAmmoData());
}
