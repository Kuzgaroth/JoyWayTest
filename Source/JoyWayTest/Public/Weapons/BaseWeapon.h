
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoyWayTest/Public/CoreTypes.h"
#include "BaseWeapon.generated.h"

DECLARE_EVENT_OneParam(ABaseWeapon, FOnReloadEvent, UAnimMontage*)
DECLARE_EVENT_OneParam(ABaseWeapon, FOnShotMadeEvent, UAnimMontage*)
DECLARE_EVENT_TwoParams(ABaseWeapon, FOnAmmoChangedEvent, int32, int32)

UCLASS(Abstract)
class JOYWAYTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ABaseWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	USkeletalMeshComponent* WeaponMesh;
	
	UPROPERTY(EditDefaultsOnly, Category="Ammo")
	FAmmoData MaxAmmo;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* ReloadAnim;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* RecoilAnim;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	UTexture2D* InventoryIcon;
	
	UPROPERTY(EditDefaultsOnly, Category="Shooting Params")
	float ShootingRange;
	UPROPERTY(EditDefaultsOnly, Category="Shooting Params")
	float TimeBetweenShots;
	UPROPERTY(EditDefaultsOnly, Category="Shooting Params")
	FName MuzzelSocketName;

	UPROPERTY(EditInstanceOnly, Category="Id")
	int32 Id=0;
	
	virtual void MakeShot();
	void ConsumeAmmo();
	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd);
	void GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;
	FTimerHandle FireHandle;
public:
	void ReloadAmmo();
	void SetAmmo(FAmmoData NewAmmoData = {});
	bool CanFire() const;
	bool CanReload() const;
	void ForceReload();
	virtual void StartFire();
	virtual void StopFire();
	void SetActive() const;
	FOnReloadEvent& OnReload() {return OnReloadEvent;}
	FOnShotMadeEvent& OnShotMade() {return OnShotMadeEvent;}
	FOnAmmoChangedEvent& OnAmmoChanged() {return OnAmmoChangedEvent;}
	int32 GetWeaponId() const;
	FORCEINLINE const FAmmoData& GetCurrentAmmoData() const {return CurrentAmmo;}
	FORCEINLINE const UTexture2D* GetInventoryIcon()const{return  InventoryIcon;}
private:
	FAmmoData CurrentAmmo;
	FOnReloadEvent OnReloadEvent;
	FOnShotMadeEvent OnShotMadeEvent;
	FOnAmmoChangedEvent OnAmmoChangedEvent;
	
};
