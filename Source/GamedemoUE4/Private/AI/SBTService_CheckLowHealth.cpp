// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	AAIController* AIC = OwnerComp.GetAIOwner();
	if(ensure(AIC))
	{
		ASAICharacter* AI = Cast<ASAICharacter>(AIC->GetPawn()) ;
		if(AI)
		{
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributeComponent(AI);
			if(ensure(AttributeComp))
			{
				bool IsLowHealth = AttributeComp->Health <= 40.0f;
				BlackboardComp->SetValueAsBool(bLowHealth.SelectedKeyName,AttributeComp->Health <= 40.0f);
			}
		}
	}
}
