// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	Life = MaxLife;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ULifeComponent::DamageTaken);
	TankGameModeBase = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(this));
}

void ULifeComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0) return;

	Life -= Damage;
	if (Life <= 0 && TankGameModeBase)
	{
		TankGameModeBase->ActorDied(DamagedActor);
	}
		
	UE_LOG(LogTemp, Warning, TEXT("Life: %i"), Life);
}

// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

