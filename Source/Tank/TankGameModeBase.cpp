// Copyright Epic Games, Inc. All Rights Reserved.


#include "TankGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "TankPlayer.h"
#include "TankPlayerController.h"
#include "TankEnemy.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
			PlayerTank->HandleDestruction();
		}
		GameOver(false);
	}
	else if (ATankEnemy* DestroyedEnemy = Cast<ATankEnemy>(DeadActor))
	{
		DestroyedEnemy->HandleDestruction();
		if (--TargetEnemies == 0)
		{
			GameOver(true);
		}
	}
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TargetEnemies = GetTargetEnemiesCount();
	PlayerTank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

void ATankGameModeBase::HandleGameStart()
{
	if (TankPlayerController)
	{
		TankPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		const FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(TankPlayerController, &ATankPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 ATankGameModeBase::GetTargetEnemiesCount()
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this, ATankEnemy::StaticClass(), Enemies);
	return Enemies.Num();
}

