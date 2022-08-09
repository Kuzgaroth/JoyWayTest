// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WrapBox.h"

#include "WeaponInventoryWidget.generated.h"

class UItemWidget;

UCLASS()
class JOYWAYTEST_API UWeaponInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UWrapBox* WeaponWrapper;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UItemWidget> ItemWidgetClass;
public:
	void AddItem(const TDelegate<void()>& CallbackDelegate);
private:
	void OnItemChosen(int32 ItemIndex);
};
