// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameModeBase.h"

#include "EngineUtils.h"
#include "SAttributeComponent.h"
#include "AI/SAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

ASGameModeBase::ASGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ASGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_ExeEQS,this,&ASGameModeBase::Execute_SpawnEQS,SpawnTimerInterval,true);
}

void ASGameModeBase::Execute_SpawnEQS()
{
	UEnvQueryInstanceBlueprintWrapper* EQSWrapper =  UEnvQueryManager::RunEQSQuery(this,SpawnQuery,this,EEnvQueryRunMode::RandomBest5Pct,nullptr);
	if(ensure(EQSWrapper))
	{
		EQSWrapper->GetOnQueryFinishedEvent().AddDynamic(this,&ASGameModeBase::OnQueryCompleted);
	}
}

void ASGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp,Warning,TEXT("EQS Failed"));
		return ;
	}

	int32 Botnum = 0;
	for(TActorIterator<ASAICharacter> It(GetWorld());It;++It)
	{
		ASAICharacter* AICharacter = *It;
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(AICharacter->GetComponentByClass(USAttributeComponent::StaticClass()));
		if(AttributeComp && AttributeComp->IsAlive())
		{
			++Botnum;
		}
	}
	float MaxCount = 5;
	if(AICountCurve)
	{
		MaxCount = AICountCurve->GetFloatValue(GetWorld()->GetTimeSeconds());
	}
	if(Botnum>=MaxCount)
	{
		return ;
	}
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	if(Locations.Num()>0)
	{
		GetWorld()->SpawnActor<AActor>(MinionClass,Locations[0],FRotator::ZeroRotator);
	}
}
