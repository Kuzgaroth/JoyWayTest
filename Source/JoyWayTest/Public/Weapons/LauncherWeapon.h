
#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class ABaseProjectile;

UCLASS(meta=(ChildCannotTick))
class JOYWAYTEST_API ALauncherWeapon : public ABaseWeapon
{
	GENERATED_BODY()

public:
	ALauncherWeapon(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<ABaseProjectile> RocketClass;

	virtual void StopFire() override;
	virtual void GetTraceData(FVector& TraceStart, FVector& TraceEnd) override;
public:
	virtual void StartFire() override;
	virtual void MakeShot() override;
};
