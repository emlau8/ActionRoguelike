// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskNode_Heal.h"
#include "AIController.h"
#include "AI/SAICharacter.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTaskNode_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn)
		{
			// Attempt casting to ASAICharacter
			ASAICharacter* AICharacter = Cast<ASAICharacter>(MyPawn);
			if (AICharacter)
			{
				AICharacter->HealSelf();

				return EBTNodeResult::Succeeded;;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
