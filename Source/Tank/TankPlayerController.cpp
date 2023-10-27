// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (!GetPawn()) { 
		UE_LOG(LogTemp, Warning, TEXT("No pawn found!"));
		return;
	}
	
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bPlayerEnabled;
}