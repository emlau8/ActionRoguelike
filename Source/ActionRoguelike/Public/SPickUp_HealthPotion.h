// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUp_Base.h"
#include "SPickUp_HealthPotion.generated.h"


class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickUp_HealthPotion : public ASPickUp_Base
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	FText GetInteractText_Implementation(APawn* InstigatorPawn) override;
	
	ASPickUp_HealthPotion();
};
