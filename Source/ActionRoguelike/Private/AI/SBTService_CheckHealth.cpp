// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckHealth.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SAttributeComponent.h"



void USBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	// Check if Health is Low: 30%

	
	
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp))
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			APawn* AIPawn = MyController->GetPawn();
            		if (ensure(AIPawn))
            		{
            			// Get Attribute Component
            			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(AIPawn);
            			if (ensure(AttributeComp))
            			{
            				if (AttributeComp->IsLowHealth())
            				{
            					BlackBoardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, true);
            				}
            			}
            		}
		}
	}
}
