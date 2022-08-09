// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "AICharacter.generated.h"

class UWidgetComponent;

UCLASS()
class JOYWAYTEST_API AAICharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AAICharacter(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	UWidgetComponent* WidgetComponent;

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
