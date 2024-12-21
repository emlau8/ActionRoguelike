// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SBaseProjectile.h"
#include "SDashProjectile.generated.h"

class UParticleSystemComponent;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASDashProjectile : public ASBaseProjectile
{
	GENERATED_BODY()

public:	
// Sets default values for this actor's properties
ASDashProjectile();

protected:

UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
UParticleSystemComponent* ExplosionComp;
	
};