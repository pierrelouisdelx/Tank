// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TankPlayer.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankPlayer : public ABasePawn
{
    GENERATED_BODY()

public:
    ATankPlayer();
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(EditAnywhere, Category="Movement")
    float Speed = 200.f;
    void Move(float Value);
	
};
