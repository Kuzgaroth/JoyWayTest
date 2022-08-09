
#include "Components/HealthComponent.h"
#include "JoyGameInstance.h"

UHealthComponent::UHealthComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	
	if (HealthLogDescription.IsEmpty()) HealthLogDescription = "Health is at";
	if (DeathLogDescription.IsEmpty()) DeathLogDescription = "Character has died";
	
}

void UHealthComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnDied().Clear();
	OnHealthUpdated().Clear();
	
	Super::EndPlay(EndPlayReason);
}

void UHealthComponent::OnNewHealth(const float NewHealth)
{
	CurrentHealth = NewHealth;

	LogFloat(CurrentHealth, HealthLogDescription);
	
	OnHealthUpdatedEvent.Broadcast(CurrentHealth/MaxHealth);
	if (FMath::IsNearlyZero(CurrentHealth))
	{
		LogString(DeathLogDescription);
		OnDiedEvent.Broadcast(GetOwner()->GetInstigatorController());
	}
}

void UHealthComponent::SetDefaults()
{
	Super::SetDefaults();
	OnNewHealth(MaxHealth);
}

void UHealthComponent::HandleDamageEvent(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                         AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetOwner()==DamagedActor)
	{
		if (Damage<0) return;

		Damage = FMath::Clamp(Damage, 0.f, CurrentHealth);
		const auto NewHealth = CurrentHealth-Damage;
		
		OnNewHealth(NewHealth);
	}
}
