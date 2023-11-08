// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASGameModeBase();
	virtual void StartPlay() override;

	UFUNCTION(Exec)
		void WhoIsYourDaddy();
	UFUNCTION()
		virtual void OnActorKill(AActor* VictimActor,AActor* Killer);
protected:
	FTimerHandle TimerHandle_ExeEQS;

	UPROPERTY(EditDefaultsOnly,Category="Control")
		float SpawnTimerInterval;
	UPROPERTY(EditDefaultsOnly,Category="Control")
	    UEnvQuery* SpawnQuery;
	UPROPERTY(EditDefaultsOnly,Category="Control")
		UCurveFloat* AICountCurve;
	UPROPERTY(EditDefaultsOnly,Category="AI")
		TSubclassOf<AActor> MinionClass;
protected:
	void Execute_SpawnEQS();

	UFUNCTION()
		void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	
};
