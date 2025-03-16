// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPickUp_Base.h"
#include "SPickUp_Coin.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickUp_Coin : public ASPickUp_Base
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

public:
	
	ASPickUp_Coin();
};
