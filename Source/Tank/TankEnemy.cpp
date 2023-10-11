// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEnemy.h"
#include "TankPlayer.h"
#include "Kismet/GameplayStatics.h"

void ATankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());

		if (Distance <= FireRange)
		{
			RotateTurret(PlayerTank->GetActorLocation());
		}
	}
}

void ATankEnemy::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATankPlayer>(UGameplayStatics::GetPlayerPawn(this, 0));
}
