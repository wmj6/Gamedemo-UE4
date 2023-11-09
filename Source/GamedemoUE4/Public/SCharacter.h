// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class USActionComponent;
class USAttributeComponent;
class USInteractionComponent;
class UCameraComponent;
class USpringArmComponent;
UCLASS()
class GAMEDEMOUE4_API ASCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	
	void MoveRight(float value);

	void SecondarySkill();

	void Interact();

	void PrimarySkill();

	void SprintStart();

	void SprintStop();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,float Delta);
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	USInteractionComponent* InteractionComp;
	//attribute component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USAttributeComponent* AttributeComp;
	//action component
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USActionComponent* ActionComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual FVector GetPawnViewLocation() const override;
};
