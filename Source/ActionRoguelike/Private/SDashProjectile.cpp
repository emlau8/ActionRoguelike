// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ProfilingDebugging/CookStats.h"


// Sets default values
ASDashProjectile::ASDashProjectile()
{
	bHitOccurred = false;
}

// Called when the game starts or when spawned
void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComp)
	{
		SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectile::OnHit);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASDashProjectile::Dash_TeleportEffect, 0.5f);
	
}

void ASDashProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!bHitOccurred)
	{
		bHitOccurred = true; // Register that a hit has occurred

		// Cancel the timer to avoid triggering teleportation twice
		GetWorldTimerManager().ClearTimer(TimerHandle);

		Dash_TeleportEffect(); // Trigger the teleport effect immediately
	}
}

void ASDashProjectile::Dash_TeleportEffect()
{
	// Check if teleport effect needs to be spawned
	if (TeleportEffect)
	{
		SpawnLocation = GetActorLocation(); // Spawn at actor's Location
		FRotator SpawnRotation = GetActorRotation();
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TeleportEffect, SpawnLocation, SpawnRotation);
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ASDashProjectile::Dash_TeleportPawn, 0.2f);
}

void ASDashProjectile::Dash_TeleportPawn()
{
	APawn* PlayerPawn = Cast<APawn>(GetInstigator());

	if (PlayerPawn)
	{
		// Teleport Player to hit location
		PlayerPawn->SetActorLocation(SpawnLocation);
	}

	// Destroy the projectile
	Destroy();
}