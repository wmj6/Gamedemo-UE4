// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTService_CheckLowHealth.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API USBTService_CheckLowHealth : public UBTService
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector bLowHealth;
private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
