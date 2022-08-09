// Fill out your copyright notice in the Description page of Project Settings.


#include "Players/JoyPlayerController.h"

#include "Characters/BaseCharacter.h"
#include "Players/JoyPlayerState.h"
#include "UI/JoyHUD.h"

void AJoyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	FInputActionBinding InventoryBinding("Inventory", IE_Pressed);
	InventoryBinding.bExecuteWhenPaused = true;
	InventoryBinding.ActionDelegate.GetDelegateForManualSet().BindUObject(this, &AJoyPlayerController::ToggleInventory);
	InputComponent->AddActionBinding(InventoryBinding);
}

void AJoyPlayerController::InitPlayerState()
{
	Super::InitPlayerState();

	const auto JoyPlayerState = GetPlayerState<AJoyPlayerState>();
	JoyPlayerState->OnWeaponRegistered().AddUObject(this, &AJoyPlayerController::AddWeaponToInventory);
	JoyPlayerState->OnWeaponSelected().AddUObject(this, &AJoyPlayerController::CreateCurrentWeapon);
}

void AJoyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AJoyPlayerController::ToggleInventory()
{
	
	if (!GetPawn()) return;

	const bool bVisibility = !bInventoryOpened;
	if (bVisibility)
	{
		const FInputModeGameAndUI UIInputMode;
		SetInputMode(UIInputMode);
	}
	else
	{
		const FInputModeGameOnly GameMode;
		SetInputMode(GameMode);
	}
	bShowMouseCursor = bVisibility;
	
	const auto HUDObj = GetHUD<AJoyHUD>();
	HUDObj->ToggleInventory(bVisibility);
	SetPause(bVisibility);
	bInventoryOpened = bVisibility;
	
}

void AJoyPlayerController::AddWeaponToInventory(const TDelegate<void()>& Callback) const
{
	const auto JoyHUD = GetHUD<AJoyHUD>();
	JoyHUD->AddItemToInventory(Callback);
}

void AJoyPlayerController::CreateCurrentWeapon(UClass* WeaponClass, const FAmmoData& AmmoData) const
{
	const auto BaseCharacter = GetPawn<ABaseCharacter>();
	const auto HUD = GetHUD<AJoyHUD>();
	BaseCharacter->SetupWeapon(WeaponClass, AmmoData, HUD->GetWeaponDelegate());

	
}
