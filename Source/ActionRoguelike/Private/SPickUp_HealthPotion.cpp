// Fill out your copyright notice in the Description page of Project Settings.


#include "SPickUp_HealthPotion.h"
#include "SAttributeComponent.h"
#include "SPlayerState.h"



#define LOCTEXT_NAMESPACE "InteractableActors"


ASPickUp_HealthPotion::ASPickUp_HealthPotion()
{
	CreditCost = 50;
}


void ASPickUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	// Check if not already at max health
	if (ensure(AttributeComp) && !AttributeComp->IsFullHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{
			if (PS->GetCredit() >= CreditCost)
			{
				if (PS->RemoveCredit(CreditCost)&& AttributeComp->ApplyHealthChange(this, AttributeComp->GetHealthMax()))
                {
                	// Only activate if healed successfully
                	HideAndCooldownPickUp();
                }
			}
			
		}
	}
}


FText ASPickUp_HealthPotion::GetInteractText_Implementation(APawn* InstigatorPawn)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);
	if (AttributeComp && AttributeComp->IsFullHealth())
	{
		return LOCTEXT("FullHealthWarning", "Already at full health.");
	}

	return FText::Format(LOCTEXT("HealthPotion_InteractMessage", "Cost {0} Credits, Restores health to maximum."), CreditCost);
}


#undef LOCTEXT_NAMESPACE