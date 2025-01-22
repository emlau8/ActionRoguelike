// Fill out your copyright notice in the Description page of Project Settings.


#include "SBasePickUp.h"
#include "Engine/Engine.h"
#include "SAttributeComponent.h"


// Sets default values
ASBasePickUp::ASBasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

	IdleDelay =  10.0f;
	
}

// Called when the game starts or when spawned
void ASBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASBasePickUp::Interact_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (AttributeComp)
	{
		if (AttributeComp->Health == AttributeComp->HealthMax)
		{
			// Do Nothing
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Nope"));
			}
		}
		else
		{
			// Slurp that thang
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Gluup...Gluup...Gluuuup!"));
			}
		
			AttributeComp->ApplyHealthChange(40.0f);
		
			MeshComp->SetVisibility(false);
			MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			GetWorldTimerManager().SetTimer(Timer_Idle, this, &ASBasePickUp::Idle_End, IdleDelay, false);
		}
	}
}

void ASBasePickUp::Idle_End()
{
	MeshComp->SetVisibility(true);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}
