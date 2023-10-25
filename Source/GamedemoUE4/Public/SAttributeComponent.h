// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged,AActor*,InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth,float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEMOUE4_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attribute")
		float Health;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
public:	
	UFUNCTION(BlueprintCallable,Category = "Attribte")
	bool ApplyHealthChange(float Delta);

	UFUNCTION(BlueprintCallable)
		bool IsAlive();
};
