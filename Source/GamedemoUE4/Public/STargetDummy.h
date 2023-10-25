// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;

UCLASS()
class GAMEDEMOUE4_API ASTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTargetDummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		USAttributeComponent* AttributeComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetDummyHit(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,float Delta);
};
