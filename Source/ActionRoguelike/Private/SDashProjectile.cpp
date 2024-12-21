// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
	UParticleSystemComponent* ExplosionComp = CreateDefaultSubobject<UParticleSystemComponent>("ExplosionComp");
	ExplosionComp->SetupAttachment(ASBaseProjectile::RootComponent);
}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	
	
}