// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"


void ASPlayerState::ApplyCreditChange(int32 Amount)
{
	if (Amount < 0.0f)
	{
		Credit += Amount;
	}
}
