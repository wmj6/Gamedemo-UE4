// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ASBlackholeProjectile::ASBlackholeProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(RootComponent);
	ForceComp->ForceStrength = -50000;
	ForceComp->Radius = 1000.0f;
	ForceComp->bImpulseVelChange = true;
	ForceComp->bAutoActivate = true;
	ForceComp->bIgnoreOwningActor = true;
	
	MovementComp->ProjectileGravityScale = 0;
	MovementComp->InitialSpeed = 500.0f;
	SphereComp->SetSphereRadius(54);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASBlackholeProjectile::OnBeginOverlap);
}

void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	ForceComp->SetActive(false);
	GetWorldTimerManager().SetTimer(TimerHandle_trigger,this,&ASBlackholeProjectile::SuckEvering,4.0f);
}

void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASBlackholeProjectile::SuckEvering()
{
	ForceComp->SetActive(true);
	auto DestoryBlackHole = [this]
	{
		Destroy();
	};
	GetWorldTimerManager().SetTimer(TimerHandle_destory,DestoryBlackHole,2.0f,false);
	
}

void ASBlackholeProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("12344444"));
	OtherActor->Destroy();
}
