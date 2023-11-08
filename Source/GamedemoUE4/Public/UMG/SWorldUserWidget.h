// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"

class USizeBox;
/**
 * 
 */
UCLASS()
class GAMEDEMOUE4_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
		void SetAttachedActor(AActor* _AttachedActor){
			AttachedActor = _AttachedActor;
		}
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
protected:
	UPROPERTY(BlueprintReadOnly)
	AActor* AttachedActor;

	UPROPERTY(meta = (BindWidget))
		USizeBox* ParentSizeBox;
	
	UPROPERTY(EditAnywhere)
		FVector WorldOffset;
};
