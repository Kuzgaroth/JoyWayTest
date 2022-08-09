
#include "Characters/BaseCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WeaponComponent.h"
#include "Players/JoyPlayerState.h"

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

	
}

void ABaseCharacter::SetPlayerDefaults()
{
	Super::SetPlayerDefaults();

	HealthComponent->SetDefaults();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnCapsuleOverlap);
	
}

void ABaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//GetCapsuleComponent()->OnComponentBeginOverlap.Clear();
	Super::EndPlay(EndPlayReason);
}

void ABaseCharacter::ConnectHealthComponent(const TDelegate<void(AController*)>& DeathDelegate, const TDelegate<void(float)>& DamageDelegate)
{
	HealthComponent->OnDied().Add(DeathDelegate);
	HealthComponent->OnHealthUpdated().Add(DamageDelegate);
	OnTakeAnyDamage.AddDynamic(HealthComponent, &UHealthComponent::HandleDamageEvent);
}

void ABaseCharacter::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		const auto Data = WeaponComponent->TryPickupWeapon(OtherActor);
		if (!Data.GetItemData().IsEmpty())
		{
			GetPlayerStateChecked<AJoyPlayerState>()->RegisterNewWeapon(Data);
			OtherActor->Destroy();
		}
		
	}
}

void ABaseCharacter::SetupWeapon(UClass* WeaponClass, const FAmmoData& AmmoData,
	const TDelegate<void(int32, int32)>& AmmoDelegate)
{
	WeaponComponent->StopFire();
	WeaponComponent->SpawnWeapon(WeaponClass, AmmoData, GetMesh(), AmmoDelegate,WeaponSocketName);
}
