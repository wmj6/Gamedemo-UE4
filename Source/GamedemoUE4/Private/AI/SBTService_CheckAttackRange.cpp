// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();

	if(ensure(BlackBoardComp))
	{
		const AActor* target = Cast<AActor>(BlackBoardComp->GetValueAsObject("Target"));
		if(target)
		{
			const AAIController* AiPC = OwnerComp.GetAIOwner();
			if(ensure(AiPC))
			{
				const APawn* AiPawn = AiPC->GetPawn();
				if(ensure(AiPawn))
				{
					const float distance = FVector::Distance(target->GetActorLocation(),AiPawn->GetActorLocation());
					const bool bInRange = distance < 2000.0f;

					bool bHasSight = AiPC->LineOfSightTo(target);
					BlackBoardComp->SetValueAsBool(bInAttackRange.SelectedKeyName,bInRange&&bHasSight);
				}
			}
		}
	}
}
