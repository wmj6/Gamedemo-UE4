// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPotion.h"
#include "SPotion_Health.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API ASPotion_Health : public ASPotion
{
	GENERATED_BODY()
public:
	ASPotion_Health();
public:
	UFUNCTION()
		virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	UFUNCTION()
		void OnBeginInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	virtual void PostInitializeComponents() override;
};
