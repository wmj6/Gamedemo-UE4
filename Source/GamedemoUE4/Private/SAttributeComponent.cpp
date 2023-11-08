// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}

USAttributeComponent* USAttributeComponent::GetAttributeComponent(AActor* FromActor)
{
	if(ensure(FromActor))
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	UE_LOG(LogTemp,Error,TEXT("have no AimActor"));
	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* FromActor)
{
	USAttributeComponent* AttributeComp = GetAttributeComponent(FromActor);
	if(AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false;
}

bool USAttributeComponent::ApplyHealthChange(AActor* Instigator,float Delta)
{
	if(!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	if(Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
		Delta *= DamageMultiplier;
	}
	
	float OldHealth = Health;
	Health = FMath::Clamp<float>(Health + Delta,0,HealthMax);
	float RealDelta = Health - OldHealth;
	UE_LOG(LogTemp,Warning,TEXT("%f"),Delta);
	OnHealthChanged.Broadcast(Instigator,this,Health,RealDelta);

	//Player Died
	if(RealDelta <=0.0f && Health == 0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if(GM)
		{
			GM->OnActorKill(GetOwner(),Instigator);
		}
	}
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

