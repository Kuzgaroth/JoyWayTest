// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JoyWayTestGameMode.generated.h"

UCLASS(minimalapi)
class AJoyWayTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJoyWayTestGameMode();
protected:
	UPROPERTY(EditDefaultsOnly, Category="Respawn")
	float RespawnTime = 2.f;
	
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
private:
	void StartRespawn(AController* NewController, FTimerHandle RespawnHandle);
};



