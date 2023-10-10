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
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Movement")
    float Speed = 200.f;

    UPROPERTY(EditAnywhere, Category="Movement")
    float TurnRate = 45.f;
    
    void Move(float Value);
    void Turn(float Value);

    APlayerController* PlayerControllerRef;
};
