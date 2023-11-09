// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction.h"

#include "SActionComponent.h"


bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if(bIsRunning)
	{
		return false;
	}
	USActionComponent* Comp = GetOwningComponent();
	if(Comp && Comp->ActiveGameplayTags.HasAny(BlockTags))
	{
		return false;
	}
	return true;
}

void USAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT("Start Action"));
	USActionComponent* Comp = GetOwningComponent();
	if(Comp)
	{
		Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	}
	bIsRunning = true;
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp,Warning,TEXT("Stop Action"));
	
	ensureAlways(bIsRunning);
	
	USActionComponent* Comp = GetOwningComponent();
	if(Comp)
	{
		
		Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	}
	bIsRunning = false;
}

USActionComponent* USAction::GetOwningComponent()
{
	return Cast<USActionComponent>(GetOuter());
}

UWorld* USAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
}
