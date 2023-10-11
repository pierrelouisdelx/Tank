// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankEnemy : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	class ATankPlayer* PlayerTank;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.0f;
};
