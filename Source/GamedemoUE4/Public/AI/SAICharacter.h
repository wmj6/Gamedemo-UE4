// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SAICharacter.generated.h"

class USWorldUserWidget;
class USAttributeComponent;
class UPawnSensingComponent;

UCLASS()
class GAMEDEMOUE4_API ASAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
		UPawnSensingComponent* SensingComp;
	UPROPERTY()
		USAttributeComponent* AttributeComp;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<USWorldUserWidget> HealthBarWidgetClass;
	UPROPERTY()
		USWorldUserWidget* ActiveHealthBarWidget;

	FTimerHandle TimerHandle_RemoveHealthBar;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
		void OnSeePawn(APawn* Pawn);
	UFUNCTION()
		void OnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,float Delta);
	UFUNCTION()
		void SetAimTarget(AActor* NewTarget);
};
