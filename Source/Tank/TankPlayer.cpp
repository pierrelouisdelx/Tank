// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayer.h"
#include "Components/InputComponent.h"

ATankPlayer::ATankPlayer()
{
    UE_LOG(LogTemp, Warning, TEXT("ATankPlayer"));
}

void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent"));
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPlayer::Move);
}

void ATankPlayer::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value;
    AddActorLocalOffset(DeltaLocation);
    UE_LOG(LogTemp, Warning, TEXT("Player Move: %f"), Value);
}

