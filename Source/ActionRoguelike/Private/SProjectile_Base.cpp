// Fill out your copyright notice in the Description page of Project Settings.

#include "SProjectile_Base.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASProjectile_Base::ASProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ASProjectile_Base::OnActorHit);
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	// Initialize the audio Component
	FlightSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FlightSoundComponent"));
	FlightSoundComponent->SetupAttachment(RootComponent);


	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->InitialSpeed = 8000.0f;

	SetReplicates(true);
}

void ASProjectile_Base::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

// _Implementation from it being marked as BlueprintNativeEvent
void ASProjectile_Base::Explode_Implementation()
{
	// Check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKillPending()))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		UGameplayStatics::PlaySoundAtLocation(this, ImpactSoundCue, GetActorLocation(), GetActorRotation());

		// Camera Shake
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ClientStartCameraShake(CameraShake);
		}
		
		Destroy();
	}
}

void ASProjectile_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ASProjectile_Base::BeginPlay()
{
	Super::BeginPlay();

	// Play looped sound
	if (ensure(FlightSoundComponent))
	{
		FlightSoundComponent->Play();
	}
}