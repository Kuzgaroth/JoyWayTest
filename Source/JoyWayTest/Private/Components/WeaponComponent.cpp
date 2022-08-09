// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapons/BaseWeapon.h"


UWeaponComponent::UWeaponComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentWeapon) CurrentWeapon->Destroy();
	Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::SetCurrentWeapon(ABaseWeapon* NewWeapon)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(nullptr);
		CurrentWeapon->Destroy();
	}
	
	
	CurrentWeapon = NewWeapon;
	CurrentWeapon->OnReload().AddUObject(this, &UWeaponComponent::ReloadWeapon);
	CurrentWeapon->SetActive();
}

void UWeaponComponent::ReloadWeapon(UAnimMontage* ReloadAnim)
{
	if (ReloadAnim)
	{
		const auto AnimInst =GetOwner<ACharacter>()->GetMesh()->GetAnimInstance();
		AnimInst->Montage_Play(ReloadAnim);
		FOnMontageBlendingOutStarted MontageDelegate = FOnMontageBlendingOutStarted::CreateLambda(
			[&](UAnimMontage* Anim, bool bInterrupted)
		{
			CurrentWeapon->ReloadAmmo();
				bReloading = false;
		});
		AnimInst->Montage_SetBlendingOutDelegate(MontageDelegate, ReloadAnim);
		bReloading = true;
	} else CurrentWeapon->ReloadAmmo();
	
}

void UWeaponComponent::SetDefaults()
{
	
	Super::SetDefaults();
}

void UWeaponComponent::StartFire()
{
	if (CurrentWeapon && CurrentWeapon->CanFire() && !bReloading) CurrentWeapon->StartFire();
	
}

void UWeaponComponent::StopFire()
{
	if (CurrentWeapon) CurrentWeapon->StopFire();
}

void UWeaponComponent::Reload()
{
	if (CurrentWeapon && CurrentWeapon->CanReload() && !bReloading) CurrentWeapon->ForceReload();
}

void UWeaponComponent::SpawnWeapon(UClass* WeaponClass, const FAmmoData& AmmoData,
	USkeletalMeshComponent* CharacterMesh, const TDelegate<void(int32, int32)>& AmmoDelegate, const FName& SpawnSocket)
{
	const auto Transform = CharacterMesh->GetSocketTransform(SpawnSocket);
	ABaseWeapon* Weapon = GetWorld()->SpawnActorDeferred<ABaseWeapon>(WeaponClass,Transform, GetOwner(),
		GetOwner<APawn>(), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Weapon->SetActorEnableCollision(false);
	Weapon->SetAmmo(AmmoData);
	Weapon->FinishSpawning(Transform);

	Weapon->OnAmmoChanged().Add(AmmoDelegate);
	Weapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SpawnSocket);
	SetCurrentWeapon(Weapon);
}

FWeaponSaveData UWeaponComponent::TryPickupWeapon(AActor* PossibleWeapon) const
{
	const auto Weapon = Cast<ABaseWeapon>(PossibleWeapon);
	FWeaponSaveData SaveData{};
	if (Weapon)
	{
		const auto ItemData = FWeaponItemData(Weapon->GetWeaponId(), TSubclassOf<ABaseWeapon>(Weapon->GetClass()));
		SaveData = FWeaponSaveData(ItemData, Weapon->GetCurrentAmmoData());
	}
	return SaveData;
}

