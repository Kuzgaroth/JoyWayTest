
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UI/WeaponWidget.h"
#include "PlayerGameWidget.generated.h"


UCLASS()
class JOYWAYTEST_API UPlayerGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UWeaponWidget> WeaponWidgetClass;

	virtual void NativeOnInitialized() override;
private:
	UPROPERTY()
	UWeaponWidget* WeaponWidget;
public:
	FORCEINLINE UProgressBar* GetHealthBar() const {return HealthBar;}
	FORCEINLINE UWeaponWidget* GetWeaponWidget() const {return WeaponWidget;}

	virtual void SetVisibility(ESlateVisibility InVisibility) override;
};
