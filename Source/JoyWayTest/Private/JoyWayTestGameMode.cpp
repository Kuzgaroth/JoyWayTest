
#include "JoyWayTestGameMode.h"
#include "Characters/BaseCharacter.h"
#include "Players/JoyPlayerController.h"
#include "Players/JoyPlayerState.h"
#include "UI/JoyHUD.h"

AJoyWayTestGameMode::AJoyWayTestGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	HUDClass = AJoyHUD::StaticClass();
	PlayerStateClass = AJoyPlayerState::StaticClass();
	PlayerControllerClass = AJoyPlayerController::StaticClass();
	
}

void AJoyWayTestGameMode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{

	if (NewPlayer->GetPawn() == nullptr)
	{
		NewPlayer->FailedToSpawnPawn();
		return;
	}
	
	const auto PlayerPawn = NewPlayer->GetPawn<ABaseCharacter>();

	TDelegate<void(AController*)> PlayerDeathDelegate;
	PlayerDeathDelegate.BindLambda([&](AController* PC)
	{
		PC->GetPawn()->Reset();
		PC->ChangeState(NAME_Spectating);
		FTimerHandle RespawnHandle;
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUObject(this, &AJoyWayTestGameMode::StartRespawn, PC, RespawnHandle);
		GetWorldTimerManager().SetTimer(RespawnHandle, TimerDelegate, RespawnTime, false);
		
	});
	TDelegate<void(float)> PlayerDamagedDelegate;
	const auto PlayerController = Cast<APlayerController>(NewPlayer);
	if (PlayerController)
	{
		const auto HUD = PlayerController->GetHUD<AJoyHUD>();
		PlayerDamagedDelegate = HUD->GetHealthDelegate();
		
	}
	PlayerPawn->ConnectHealthComponent(PlayerDeathDelegate, PlayerDamagedDelegate);
	
	Super::FinishRestartPlayer(NewPlayer, StartRotation);
}

void AJoyWayTestGameMode::StartRespawn(AController* NewController, FTimerHandle RespawnHandle)
{
	RestartPlayer(NewController);
	GetWorldTimerManager().ClearTimer(RespawnHandle);
}
