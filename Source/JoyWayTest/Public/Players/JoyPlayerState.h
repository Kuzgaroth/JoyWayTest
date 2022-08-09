// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JoyWayTest/Public/CoreTypes.h"
#include "JoyPlayerState.generated.h"

DECLARE_EVENT_OneParam(AJoyPlayerState, FOnWeaponRegisteredEvent, const TDelegate<void()>&)
DECLARE_EVENT_TwoParams(AJoyPlayerState, FOnWeaponSelectedEvent, UClass*, const FAmmoData&)

UCLASS()
class JOYWAYTEST_API AJoyPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FWeaponSaveData> WeaponItemDatas;
	UPROPERTY()
	FWeaponSaveData CurrentWeaponItem;
private:
	FOnWeaponRegisteredEvent OnWeaponRegisteredEvent;
	FOnWeaponSelectedEvent OnWeaponSelectedEvent;
	TDelegate<void()> CallbackDelegate;

	void UpdateAmmoData(const FAmmoData& NewData, FAmmoData& OldData);
public:
	void RegisterNewWeapon(const FWeaponSaveData& NewWeaponData);
	void SelectNewWeapon(int32 Index);
	FOnWeaponRegisteredEvent& OnWeaponRegistered(){return OnWeaponRegisteredEvent;}
	FOnWeaponSelectedEvent& OnWeaponSelected(){return OnWeaponSelectedEvent;}
};
