// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUp_Base.h"
#include "Components/SphereComponent.h"


// Sets default values
ASPickUp_Base::ASPickUp_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("PickUp");
	RootComponent = SphereComp;

	RespawnTime =  10.0f;
	
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