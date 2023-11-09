// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/SAction.h"
#include "SAction_ProjectileAttack.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API USAction_ProjectileAttack : public USAction
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ProjectileClass;
	UPROPERTY(EditAnywhere)
		UAnimMontage* AttackAnim;
	UPROPERTY(VisibleAnywhere)
		FName HandSocketName;
	UPROPERTY(VisibleAnywhere)
		float AttackAnimDelay;
public:
	USAction_ProjectileAttack();
	
	virtual void StartAction_Implementation(AActor* Instigator) override;

	UFUNCTION()
		void AttackDelay_Elapsed(ACharacter* InstigatorCharacter);
};
