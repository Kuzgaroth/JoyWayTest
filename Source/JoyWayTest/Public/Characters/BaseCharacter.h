
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoyWayTest/Public/CoreTypes.h"
#include "BaseCharacter.generated.h"

class UHealthComponent;
class UWeaponComponent;

UCLASS()
class JOYWAYTEST_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category="Components")
	UWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category="Sockets")
	FName WeaponSocketName;
	
	virtual void SetPlayerDefaults() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	virtual void ConnectHealthComponent(const TDelegate<void(AController*)>& DeathDelegate,
		const TDelegate<void(float)>&  DamageDelegate);
	virtual void SetupWeapon(UClass* WeaponClass, const FAmmoData& AmmoData, const TDelegate<void(int32, int32)>& AmmoDelegate);
private:
	UFUNCTION()
	void OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	 int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
