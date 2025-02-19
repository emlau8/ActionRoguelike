// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"




void ASPlayerState::AddCredit(int32 Delta)
{
	// Avoid user-error of adding a negative amount or zero
	if (!ensure(Delta > 0.0f))
	{
		return;
	}
	
	Credit += Delta;
	
	OnCreditChanged.Broadcast(this, Credit, Delta);
	
}

bool ASPlayerState::RemoveCredit(int32 Delta)
{
	// Avoid user-error of adding a subtracting negative amount or zero
	if (!ensure(Delta > 0.0f))
	{
		return false;
	}
	
	if (Credit < Delta)
	{
		// Not enough credits available
		
	}

	Credit -= Delta;
	
    OnCreditChanged.Broadcast(this, Credit, -Delta);

	return true;
}


int32 ASPlayerState::GetCredit() const
{
	return Credit;
}