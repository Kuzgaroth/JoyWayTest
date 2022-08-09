// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WeaponInventoryWidget.h"

#include "UI/ItemWidget.h"

void UWeaponInventoryWidget::AddItem(const TDelegate<void()>& CallbackDelegate)
{
	const auto NewItem = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
	NewItem->OnItemChosen().Add(CallbackDelegate);
	const auto bEmpty = WeaponWrapper->HasAnyChildren();
	WeaponWrapper->AddChildToWrapBox(NewItem);
	const auto Index = WeaponWrapper->GetChildIndex(NewItem);
	NewItem->OnItemChosen().AddUObject(this, &UWeaponInventoryWidget::OnItemChosen, Index);
	if (!bEmpty) NewItem->OnFirstInInventory();
}

void UWeaponInventoryWidget::OnItemChosen(int32 ItemIndex)
{
	auto ItemArray = WeaponWrapper->GetAllChildren();
	ItemArray.RemoveAt(ItemIndex);
	for (const auto Item : ItemArray)
	{
		const auto WeaponItem = CastChecked<UItemWidget>(Item);
		WeaponItem->AnotherHasChosen();
	}
}

