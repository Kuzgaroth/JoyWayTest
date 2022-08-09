
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JoyHUD.generated.h"

class UPlayerGameWidget;
class UWeaponInventoryWidget;

UCLASS()
class JOYWAYTEST_API AJoyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UPlayerGameWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSubclassOf<UWeaponInventoryWidget> InventoryWidgetClass;
	
	virtual void PostInitializeComponents() override;
public:
	TDelegate<void(float)> GetHealthDelegate();
	const TDelegate<void(int32, int32)>& GetWeaponDelegate() const;
	void ToggleInventory(bool bNewVisibility);
	void AddItemToInventory(const TDelegate<void()>& CallbackDelegate);
private:
	UPROPERTY()
	UPlayerGameWidget* PlayerWidget;

	UPROPERTY()
	UWeaponInventoryWidget* InventoryWidget;
};
