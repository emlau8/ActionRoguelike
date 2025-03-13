// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

#include "SSaveGame.h"


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


void ASPlayerState::SavePlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credit = Credit;
	}
}


void ASPlayerState::LoadPlayerState_Implementation(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		Credit = SaveObject->Credit;
	}
}


int32 ASPlayerState::GetCredit() const
{
	return Credit;
}
