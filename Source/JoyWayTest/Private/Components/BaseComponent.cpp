
#include "Components/BaseComponent.h"

UBaseComponent::UBaseComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBaseComponent::LogFloat(const float Value, const FString& Description)
{
	UE_LOG(LogJoyComponent, Warning, TEXT("%s: %f"), *Description, Value);
}

void UBaseComponent::LogString(const FString& Description)
{
	UE_LOG(LogJoyComponent, Warning, TEXT("%s"), *Description);
}

void UBaseComponent::SetDefaults(){}

