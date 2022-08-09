// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JoyWayTest/Public/CoreTypes.h"
#include "JoyPlayerController.generated.h"



UCLASS()
class JOYWAYTEST_API AJoyPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void SetupInputComponent() override;
	virtual void InitPlayerState() override;
	virtual void OnPossess(APawn* InPawn) override;
private:
	bool bInventoryOpened=false;
	void ToggleInventory();
	void AddWeaponToInventory(const TDelegate<void()>& Callback) const;
	void CreateCurrentWeapon(UClass* WeaponClass, const FAmmoData& AmmoData) const;
};
