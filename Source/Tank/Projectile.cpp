// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (!MyOwner) return;

	auto MyInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	auto PlayerTag = OtherActor->ActorHasTag(FName("Player"));
	auto EnemyTag = OtherActor->ActorHasTag(FName("Enemy"));
	auto ProjectileTag = OtherActor->ActorHasTag(FName("Projectile"));
	auto WallTag = OtherActor->ActorHasTag(FName("Wall"));

	if (OtherActor && OtherActor != this && OtherActor != MyOwner && EnemyTag)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit %s"), *OtherActor->GetName());
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyInstigator, this, DamageTypeClass);
		Destroy();
	}

	if (PlayerTag || ProjectileTag || WallTag)
	{
		currentBounces++;
		if (currentBounces >= maxBounces)
		{
			Destroy();
		}
	}
}

void AProjectile::setMaterial(UMaterialInstanceDynamic* Material)
{
	ProjectileMesh->SetMaterial(0, Material);
}
