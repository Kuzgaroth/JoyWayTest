// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::UpdateHealthBar(float NewValue)
{
	HealthBar->SetPercent(NewValue);
}
