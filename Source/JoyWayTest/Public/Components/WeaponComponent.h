
#pragma once

#include "CoreMinimal.h"
#include "BaseComponent.h"
#include "JoyWayTest/Public/CoreTypes.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class JOYWAYTEST_API UWeaponComponent : public UBaseComponent
{
	GENERATED_BODY()

public:
	UWeaponComponent(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Weapons")
	TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UPROPERTY()
	ABaseWeapon* CurrentWeapon;

	bool bReloading=false;
	void SetCurrentWeapon(ABaseWeapon* NewWeapon);
	void ReloadWeapon(UAnimMontage* ReloadMontage);
public:
	
	virtual void SetDefaults() override;
	void StartFire();
	void StopFire();
	void Reload();
	void SpawnWeapon(UClass* WeaponClass, const FAmmoData& AmmoData, USkeletalMeshComponent* CharacterMesh,
		const TDelegate<void(int32, int32)>& AmmoDelegate, const FName& SpawnSocket);
	FWeaponSaveData TryPickupWeapon(AActor* PossibleWeapon) const;
};
