// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayer.h"
#include "Components/InputComponent.h"

ATankPlayer::ATankPlayer()
{
}

void ATankPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPlayer::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPlayer::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATankPlayer::Fire);
}

void ATankPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
}

// Called when the game starts or when spawned
void ATankPlayer::BeginPlay()
{
    Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATankPlayer::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * GetWorld()->DeltaTimeSeconds;
    AddActorLocalOffset(DeltaLocation);
}

void ATankPlayer::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * TurnRate * GetWorld()->DeltaTimeSeconds;
    AddActorLocalRotation(DeltaRotation, true);
}

