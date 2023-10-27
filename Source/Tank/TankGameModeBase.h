// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TANK_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void HandleGameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATankPlayer* PlayerTank;
	class ATankPlayerController* TankPlayerController;

	float StartDelay = 3.f;


	int32 TargetEnemies = 0;
	int32 GetTargetEnemiesCount();
};
