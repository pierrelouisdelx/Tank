// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TANK_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	void HandleDestruction();

protected:
	void Move(float Value);
	void Turn(float Value);
	void RotateTurret(FVector LookAtTarget);
	void Fire();
	void ResetFireCooldown();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UBoxComponent* BoxComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BaseMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TurretMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, Category="Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float TurnRate = 45.f;

	UPROPERTY(EditAnywhere)
	float turretRotationSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	// Number of bullets fired without cooldown
	int32 BulletsFired;

	UPROPERTY(EditAnywhere, Category = "Combat")
	int32 MaxBulletsWithoutCooldown = 3;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float FireCooldown = 3.0f;
};
