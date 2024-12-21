// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SDashProjectile.generated.h"


/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	UParticleSystem* TeleportEffect;

	FTimerHandle TimerHandle;

	bool bHitOccurred;
	FVector SpawnLocation;

public:	

	// Sets default values for this actor's properties
	ASDashProjectile();

protected:
		
	void BeginPlay();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void Dash_TeleportEffect();
	
	void Dash_TeleportPawn();
};