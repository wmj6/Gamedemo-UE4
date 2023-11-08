// Fill out your copyright notice in the Description page of Project Settings.


#include "SPotion_Health.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

ASPotion_Health::ASPotion_Health()
{
	
}

void ASPotion_Health::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASPotion_Health::OnBeginInteract);
}

void ASPotion_Health::Interact_Implementation(APawn* InstigatorPawn)
{
	if(ensure(InstigatorPawn))
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributeComponent(InstigatorPawn);
		if(ensure(AttributeComp) && !AttributeComp->IsFullHealth())
		{
			AttributeComp->ApplyHealthChange(InstigatorPawn,20);
			Destroy();
		}
	}
}

void ASPotion_Health::OnBeginInteract(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* InstigatorPawn = Cast<APawn>(OtherActor);
	if(InstigatorPawn && Cast<AAIController>(InstigatorPawn->GetController())==nullptr)
	{
		Interact_Implementation(InstigatorPawn);
	}
}


