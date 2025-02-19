// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUp_Coin.h"
#include "SPlayerState.h"


ASPickUp_Coin::ASPickUp_Coin()
{
	CreditCost = 80;
}


void ASPickUp_Coin::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredit(CreditCost);
		HideAndCooldownPickUp();
	}
}
