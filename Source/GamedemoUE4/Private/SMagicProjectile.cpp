// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"

ASMagicProjectile::ASMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this,&ASMagicProjectile::OnActorHit);
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
	if(OtherActor && OtherActor!=GetInstigator())
	{
		bool result = USGameplayFunctionLibrary::ApplyDirectionDamage(GetInstigator(),OtherActor,-20.0f,Hit);
		UE_LOG(LogTemp,Warning,TEXT("%d"),result);
	}
}

void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

