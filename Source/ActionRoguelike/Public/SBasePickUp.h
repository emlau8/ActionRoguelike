// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SBasePickUp.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASBasePickUp : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "* PickUp")
	float IdleDelay;

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	FTimerHandle Timer_Idle;

	void Idle_End();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Sets default values for this actor's properties
	ASBasePickUp();
	
};
