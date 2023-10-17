// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "InputBehavior.h"
#include "SGameplayInterface.h"


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* owner = GetOwner();
	FVector eyeLocation,End;
	FRotator eyeRotation;
	owner->GetActorEyesViewPoint(eyeLocation,eyeRotation);

	End = eyeLocation+(eyeRotation.Vector()*1000);
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(Hit,eyeLocation,End,ObjectQueryParams);

	if(AActor* HitActor = Hit.GetActor())
	{
		if(HitActor->Implements<USGameplayInterface>())
		{
			APawn* Pawn = Cast<APawn>(owner);
			ISGameplayInterface::Execute_Interact(HitActor,Pawn);
		}
	}
}