// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerController.h"

#include "Blueprint/UserWidget.h"

void ASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void ASPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(ensure(MainHUD))
	{
		CreateWidget(this,MainHUD)->AddToViewport();
	}
}
