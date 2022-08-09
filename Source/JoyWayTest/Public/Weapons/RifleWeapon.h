
#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RifleWeapon.generated.h"

UCLASS(meta=(ChildCannotTick))
class JOYWAYTEST_API ARifleWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ARifleWeapon(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(EditDefaultsOnly, Category="Shooting Params")
	float BulletSpread;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float ShotDamage;
	
	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;
public:
	virtual void StartFire() override;
	virtual void StopFire() override;
	virtual void MakeShot() override;
private:
	
};
