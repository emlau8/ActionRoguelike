// Fill out your copyright notice in the Description page of Project Settings.

#include "SMagicProjectile.h"
#include "SAttributeComponent.h"
#include "Audio/AudioDebug.h"
#include "Components/SphereComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);

	// Initialize the audio Component
	FlightSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FlightSoundComponent"));
	FlightSoundComponent->SetupAttachment(RootComponent);

	DamageAmount = -20.0f;
	
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(DamageAmount);
		}
		
		Explode();
	}
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Play looped sound
	if (FlightSoundComponent)
	{
		FlightSoundComponent->Play();
	}
}