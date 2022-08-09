
#include "Weapons/RifleWeapon.h"
#include "Kismet/KismetSystemLibrary.h"

ARifleWeapon::ARifleWeapon(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARifleWeapon::StartFire()
{
	Super::StartFire();

	GetWorldTimerManager().SetTimer(FireHandle, this, &ARifleWeapon::MakeShot,
		TimeBetweenShots, true, 0);
}

void ARifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireHandle);
	
	Super::StopFire();

}

void ARifleWeapon::MakeShot()
{
	FVector TraceStart;
	FVector TraceEnd;
	GetTraceData(TraceStart, TraceEnd);
	FHitResult HitResult;
	
	UKismetSystemLibrary::LineTraceSingle(GetGameInstance(), WeaponMesh->GetSocketLocation(MuzzelSocketName), TraceEnd,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true);
	
	if (HitResult.bBlockingHit) HitResult.Actor.Get()->TakeDamage(ShotDamage, FDamageEvent{},
		GetInstigator()->GetController(), this);
	
	Super::MakeShot();
}

void ARifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
	FVector ViewLocation;
	FRotator ViewRotation;
	GetPlayerViewPoint(ViewLocation, ViewRotation);
	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * ShootingRange;
}