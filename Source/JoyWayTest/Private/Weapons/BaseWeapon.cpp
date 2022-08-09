
#include "Weapons/BaseWeapon.h"

ABaseWeapon::ABaseWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	RootComponent = WeaponMesh;

	
}

void ABaseWeapon::StartFire(){}

void ABaseWeapon::StopFire(){}

void ABaseWeapon::SetActive() const
{
	OnAmmoChangedEvent.Broadcast(CurrentAmmo.ClipBullets, CurrentAmmo.TotalBullets);
}

int32 ABaseWeapon::GetWeaponId() const
{
	return Id;
}

void ABaseWeapon::MakeShot()
{
	OnShotMadeEvent.Broadcast(RecoilAnim);
	ConsumeAmmo();
}

void ABaseWeapon::ConsumeAmmo()
{
	if (CurrentAmmo.ClipBullets==0)
	{
		StopFire();
		return;
	}
	OnAmmoChangedEvent.Broadcast(--CurrentAmmo.ClipBullets, CurrentAmmo.TotalBullets);
	if (CurrentAmmo.ClipBullets==0 && CurrentAmmo.TotalBullets>0)
	{
		StopFire();
		OnReloadEvent.Broadcast(ReloadAnim);
	}
	
}

void ABaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd){}

bool ABaseWeapon::CanFire() const
{
	return CurrentAmmo.ClipBullets>0;
}

bool ABaseWeapon::CanReload() const
{
	return CurrentAmmo.ClipBullets<MaxAmmo.ClipBullets && CurrentAmmo.TotalBullets>0;
}

void ABaseWeapon::ForceReload()
{
	OnReloadEvent.Broadcast(ReloadAnim);
}

void ABaseWeapon::ReloadAmmo()
{
	const auto AmmoToClip = MaxAmmo.ClipBullets - CurrentAmmo.ClipBullets;
	if (CurrentAmmo.TotalBullets>=AmmoToClip)
	{
		CurrentAmmo.ClipBullets = MaxAmmo.ClipBullets;
		CurrentAmmo.TotalBullets -= AmmoToClip;
	}
	else
	{
		CurrentAmmo.ClipBullets = CurrentAmmo.ClipBullets+CurrentAmmo.TotalBullets;
		CurrentAmmo.TotalBullets = 0;
	}

	OnAmmoChangedEvent.Broadcast(CurrentAmmo.ClipBullets, CurrentAmmo.TotalBullets);
}

void ABaseWeapon::SetAmmo(FAmmoData NewAmmoData)
{
	CurrentAmmo = NewAmmoData;
}

void ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto Controller = GetInstigatorController();
	
	if (Controller->IsPlayerController())
	{
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}
	else
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzelSocketName);
	}
}

FVector ABaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzelSocketName);
}

void ABaseWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnReloadEvent.Clear();
	OnShotMadeEvent.Clear();
	OnAmmoChangedEvent.Clear();
	Super::EndPlay(EndPlayReason);
}

void ABaseWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	CurrentAmmo = MaxAmmo;
}
