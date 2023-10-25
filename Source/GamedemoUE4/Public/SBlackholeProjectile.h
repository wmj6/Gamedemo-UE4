// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectileBase.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SBlackholeProjectile.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API ASBlackholeProjectile : public ASProjectileBase
{
	GENERATED_BODY()
public:
	ASBlackholeProjectile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;

	FTimerHandle TimerHandle_trigger;
	FTimerHandle TimerHandle_destory;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SuckEvering();
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
