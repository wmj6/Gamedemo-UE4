// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTaskNode_HealSelf.h"

#include <Actor.h>

#include "SAttributeComponent.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTaskNode_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if(ensure(AIC))
	{
		APawn* pawn = AIC->GetPawn();
		if(pawn)
		{
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributeComponent(pawn);
			if(AttributeComp)
			{
				AttributeComp->ApplyHealthChange(Cast<AActor>(AIC->GetBlackboardComponent()->GetValueAsObject("Target"))
					,AttributeComp->HealthMax);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
