// Copyright Epic Games, Inc. All Rights Reserved.


#include "TankGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "TankPlayer.h"

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if (PlayerTank->GetPlayerController())
		{
			PlayerTank->DisableInput(PlayerTank->GetPlayerController());
			PlayerTank->GetPlayerController()->bShowMouseCursor = false;
		}
	}
}

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
}

