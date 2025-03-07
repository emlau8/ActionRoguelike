// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "SPickUp_Base.h"
#include "SPickUp_Action.generated.h"

class USAction;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPickUp_Action : public ASPickUp_Base
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "PickUp")
	TSubclassOf<USAction> ActionToGrant;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
