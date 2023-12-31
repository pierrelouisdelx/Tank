// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
    RootComponent = BoxComponent;

    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
    BaseMesh->SetupAttachment(RootComponent);

    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
    TurretMesh->SetupAttachment(BaseMesh);

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	BulletsFired = 0;
}

void ABasePawn::HandleDestruction()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	Destroy();
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	const FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	const FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw + 180, 0.f);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->DeltaTimeSeconds, turretRotationSpeed));
}

void ABasePawn::Fire()
{
	if (BulletsFired >= MaxBulletsWithoutCooldown)
	{
		// Cooldown still active
		return;
	}
	
	const FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	const FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

	UMaterialInstanceDynamic* Material = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	if (Material)
	{
		Projectile->setMaterial(Material);
	}

	BulletsFired++;

	FTimerHandle FireRateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &ABasePawn::ResetFireCooldown, FireCooldown, false);
}

void ABasePawn::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalOffset(DeltaLocation);
}

void ABasePawn::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * GetWorld()->DeltaTimeSeconds;
	AddActorLocalRotation(DeltaRotation, true);
}

void ABasePawn::ResetFireCooldown()
{
	BulletsFired--;
}

