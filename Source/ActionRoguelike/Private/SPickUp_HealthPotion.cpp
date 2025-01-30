// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUp_HealthPotion.h"
#include "SAttributeComponent.h"

ASPickUp_HealthPotion::ASPickUp_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable Collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASPickUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		// Only activate if healed succesfully
		if (AttributeComp->ApplyHealthChange(this,AttributeComp->GetHealthMax()))
		{
			HideAndCooldownPickUp();
		}
		
	}
}
