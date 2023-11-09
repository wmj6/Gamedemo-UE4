// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_Sprint.h"

#include "GameFramework/CharacterMovementComponent.h"

USAction_Sprint::USAction_Sprint()
{
	ActionName = "Sprint";
}

void USAction_Sprint::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	UCharacterMovementComponent* CharacterMovementComp = Cast<UCharacterMovementComponent>(Instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(CharacterMovementComp)
	{
		CharacterMovementComp->MaxWalkSpeed += 2000.0f;
	}
}

void USAction_Sprint::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);
	UCharacterMovementComponent* CharacterMovementComp = Cast<UCharacterMovementComponent>(Instigator->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	if(CharacterMovementComp)
	{
		CharacterMovementComp->MaxWalkSpeed -= 2000.0f;
	}
}
