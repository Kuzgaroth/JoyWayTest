// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "ItemWidget.generated.h"

DECLARE_EVENT(UItemWidget, FItemChosenEvent)

UCLASS()
class JOYWAYTEST_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY(meta=(BindWidget))
	UImage* BorderImage;

	virtual void NativeOnInitialized() override;
	virtual void BeginDestroy() override;
public:
	FORCEINLINE FItemChosenEvent& OnItemChosen(){return ItemChosenEvent;}
	void AnotherHasChosen();
	void SetIcon(UTexture2D* Icon);
	void OnFirstInInventory();
private:
	UFUNCTION()
	FEventReply OnClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent);
	FItemChosenEvent ItemChosenEvent;
};
