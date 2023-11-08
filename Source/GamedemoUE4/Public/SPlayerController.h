// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API ASPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget> MainHUD;
protected:
	virtual void BeginPlay() override;
};
