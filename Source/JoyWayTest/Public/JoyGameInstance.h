
#pragma once

#include "CoreMinimal.h"
#include "JoySaveGame.h"
#include "Engine/GameInstance.h"
#include "JoyGameInstance.generated.h"

UCLASS()
class JOYWAYTEST_API UJoyGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Maps")
	TArray<FSoftObjectPath> MapReferences;

	UPROPERTY()
	UJoySaveGame* SaveGame;

	UPROPERTY(EditDefaultsOnly, Category="SaveSystem")
	FString SaveSlotName;
	
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	
public:
	void LoadPlayerHealth(float& HealthParam) const;
	const TArray<FWeaponSaveData>& LoadPlayerWeapons() const;
	void SavePlayerGame();
	void DismissSave();
private:
	void AsyncSaveLoadFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSaveGame);
};
