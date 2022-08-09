// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AICharacter.h"
#include "Components/HealthComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

void AAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnTakeAnyDamage.AddDynamic(HealthComponent, &UHealthComponent::HandleDamageEvent);
	
	HealthComponent->OnDied().AddLambda([&](AController* OwnerController)
	{
		Destroy();
	});

	HealthComponent->SetDefaults();
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetComponent && WidgetComponent->GetWidgetClass())
	{
		const auto HealthWidget = Cast<UHealthBarWidget>(WidgetComponent->GetWidget());
		HealthComponent->OnHealthUpdated().AddUObject(HealthWidget, &UHealthBarWidget::UpdateHealthBar);
	}
}
