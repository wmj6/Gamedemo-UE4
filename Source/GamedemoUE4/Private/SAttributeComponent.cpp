// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}
bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr,this,Health,Delta);
	return true;
}

bool USAttributeComponent::IsAlive()
{
	return Health>0.0f;
}

bool USAttributeComponent::IsFullHealth()
{
	return Health==HealthMax;
}

