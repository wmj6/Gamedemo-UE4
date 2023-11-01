// Fill out your copyright notice in the Description page of Project Settings.


#include "SPotion.h"

#include "NavigationSystemTypes.h"
#include "Components/SphereComponent.h"

// Sets default values
ASPotion::ASPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(30.0f);
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECollisionResponse::ECR_Overlap);
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(SphereComp);
	MeshComp->SetupAttachment(SphereComp);
}

void ASPotion::SetPotionState(bool bState)
{
	SetActorEnableCollision(bState);
	RootComponent->SetVisibility(bState,true);
}

// Called when the game starts or when spawned
void ASPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	
}

