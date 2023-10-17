// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SMagicProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GAMEDEMOUE4_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* MovementComp;
	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* EffectComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
