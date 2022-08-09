// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemWidget.h"

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	BorderImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->OnMouseButtonDownEvent.BindDynamic(this, &UItemWidget::OnClicked);
}

void UItemWidget::BeginDestroy()
{
	ItemChosenEvent.Clear();
	Super::BeginDestroy();
}

FEventReply UItemWidget::OnClicked(FGeometry MyGeometry, const FPointerEvent& MouseEvent)
{
	BorderImage->SetVisibility(ESlateVisibility::Visible);
	IconImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	ItemChosenEvent.Broadcast();
	return FEventReply(true);
}

void UItemWidget::AnotherHasChosen()
{
	BorderImage->SetVisibility(ESlateVisibility::Hidden);
	IconImage->SetVisibility(ESlateVisibility::Visible);
}

void UItemWidget::SetIcon(UTexture2D* Icon)
{
	FSlateBrush NewBrush;
	NewBrush.SetResourceObject(Icon);
	IconImage->SetBrush(NewBrush);
}

void UItemWidget::OnFirstInInventory()
{
	BorderImage->SetVisibility(ESlateVisibility::Visible);
}
