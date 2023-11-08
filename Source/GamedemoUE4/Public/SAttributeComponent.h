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

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly, Category = "Attribute")
		float HealthMax;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
public:
	UFUNCTION(BlueprintCallable)
		static USAttributeComponent* GetAttributeComponent(AActor* FromActor);
	UFUNCTION(BlueprintCallable)
	static bool IsActorAlive(AActor* FromActor);
	
	UFUNCTION(BlueprintCallable,Category = "Attribte")
		bool ApplyHealthChange(AActor* Instigator, float Delta);
	
	UFUNCTION(BlueprintCallable)
		bool IsAlive();
	UFUNCTION(BlueprintCallable)
		bool IsFullHealth();
};
