// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPickUp_Base.generated.h"


class USphereComponent;

UCLASS()
class ACTIONROGUELIKE_API ASPickUp_Base : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "_PickUp")
	float RespawnTime;

	UPROPERTY(EditAnywhere, Category = "_PickUp")
	float CollisionRadius;

	FTimerHandle Timer_Respawn;

	UFUNCTION()
	void ShowPickUp();

	void HideAndCooldownPickUp();

	void SetPickUpState(bool bNewIsActive);
	
	UPROPERTY(VisibleAnywhere, Category = "PickUp")
	USphereComponent* SphereComp;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
	ASPickUp_Base();
	
};
