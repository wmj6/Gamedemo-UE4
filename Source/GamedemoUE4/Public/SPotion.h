// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SPotion.generated.h"

class USphereComponent;

UCLASS()
class GAMEDEMOUE4_API ASPotion : public AActor,public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPotion();

	void SetPotionState(bool bState);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere)
		USphereComponent* SphereComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
