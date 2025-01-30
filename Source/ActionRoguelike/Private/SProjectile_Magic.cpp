// Fill out your copyright notice in the Description page of Project Settings.

#include "SProjectile_Magic.h"
#include "SAttributeComponent.h"
#include "Audio/AudioDebug.h"
#include "Components/SphereComponent.h"

// Sets default values
ASProjectile_Magic::ASProjectile_Magic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASProjectile_Magic::OnActorOverlap);
	
	DamageAmount = 20.0f;
	
}

void ASProjectile_Magic::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			// Minus in front of DamageAmount to apply the change as damage, not healing
			AttributeComp->ApplyHealthChange(GetInstigator(), -DamageAmount);

			// Only explode when we hit something valid
			Explode();
		}
		
		
	}
}
