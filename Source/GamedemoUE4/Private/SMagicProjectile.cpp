// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "Components/SphereComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentHit.AddDynamic(this,&ASMagicProjectile::OnActorHit);
}

void ASMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
	Explode();
	if(OtherActor && OtherActor!=GetInstigator())
	{
		/*USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributeComponent(OtherActor);
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(),-20.0f);
		}*/
		bool result = USGameplayFunctionLibrary::ApplyDirectionDamage(GetInstigator(),OtherActor,-20.0f,Hit);
		UE_LOG(LogTemp,Warning,TEXT("%d"),result);
	}
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

