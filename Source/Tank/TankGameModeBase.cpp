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
		PlayerTank->HandleDestruction();
		if (TankPlayerController)
		{
			TankPlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (ATankEnemy* DestroyedEnemy = Cast<ATankEnemy>(DeadActor))
	{
		DestroyedEnemy->HandleDestruction();
	}
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
	TankPlayerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
}

