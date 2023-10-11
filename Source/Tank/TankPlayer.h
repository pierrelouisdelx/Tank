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
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void HandleDestruction();

    APlayerController* GetPlayerController() const { return PlayerController; }

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    APlayerController* PlayerController;
};
