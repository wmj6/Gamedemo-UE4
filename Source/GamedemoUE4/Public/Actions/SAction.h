// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class GAMEDEMOUE4_API USAction : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockTags;
	
	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	bool bIsRunning;
public:
	UFUNCTION(BlueprintCallable,Category="Tags")
		USActionComponent* GetOwningComponent();
	UFUNCTION(BlueprintNativeEvent, Category="Action")
		void StartAction(AActor* Instigator);
	UFUNCTION(BlueprintNativeEvent, Category="Action")
		void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent)
		bool CanStart(AActor* Instigator);
	
	virtual UWorld* GetWorld() const override;
};
