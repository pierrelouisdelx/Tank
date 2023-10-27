// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "Kismet/GameplayStatics.h"

ULifeComponent::ULifeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Life = MaxLife;
}

// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ULifeComponent::DamageTaken);
	TankGameModeBase = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void ULifeComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) return;

	Life -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Life: %i"), Life);
	if (Life <= 0 && TankGameModeBase)
	{
		TankGameModeBase->ActorDied(DamagedActor);
	}
}

// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

