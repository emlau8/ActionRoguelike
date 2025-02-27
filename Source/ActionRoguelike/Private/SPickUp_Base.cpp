// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUp_Base.h"
#include "SPlayerState.h"
#include "Components/SphereComponent.h"



ASPickUp_Base::ASPickUp_Base()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("PickUp");
	RootComponent = SphereComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable Collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
	
	RespawnTime =  10.0f;

	SetReplicates(true);
}

void ASPickUp_Base::Interact_Implementation(APawn* InstigatorPawn)
{
	// Logic in derived classes...
}

void ASPickUp_Base::ShowPickUp()
{
	SetPickUpState(true);
}

void ASPickUp_Base::HideAndCooldownPickUp()
{
	SetPickUpState(false);

	GetWorldTimerManager().SetTimer(Timer_Respawn, this, &ASPickUp_Base::ShowPickUp, RespawnTime, false);
}

void ASPickUp_Base::SetPickUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	// Set visibility on root and all children
	RootComponent->SetVisibility(bNewIsActive, true);
}