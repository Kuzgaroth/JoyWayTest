// Fill out your copyright notice in the Description page of Project Settings.


#include "JoyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UJoyGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		FAsyncLoadGameFromSlotDelegate AsyncDelegate;
		AsyncDelegate.BindUObject(this, &UJoyGameInstance::AsyncSaveLoadFinished);
		UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, 0, AsyncDelegate);

		NewWorld->OnWorldBeginPlay.AddLambda([&]()
		{
			DismissSave();
		});
	}
}

void UJoyGameInstance::LoadPlayerHealth(float& HealthParam) const
{
	if (SaveGame) HealthParam = SaveGame->GetHealth();
}

const TArray<FWeaponSaveData>& UJoyGameInstance::LoadPlayerWeapons() const
{
	return SaveGame->GetWeapons();
}

void UJoyGameInstance::DismissSave()
{
	SaveGame = nullptr;
	/*if (SaveGame) SaveGame->ConditionalBeginDestroy();*/
}

void UJoyGameInstance::AsyncSaveLoadFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSaveGame)
{
	if (SaveSlotName == SlotName) SaveGame = CastChecked<UJoySaveGame>(LoadedSaveGame);
}
