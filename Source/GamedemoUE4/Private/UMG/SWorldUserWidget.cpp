// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/SWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void USWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(!IsValid(AttachedActor))
	{
		return ;
	}
	FVector2D ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),AttachedActor->GetActorLocation() + WorldOffset,ScreenPosition))
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition/=Scale;
		if(ParentSizeBox)
		{
			ParentSizeBox->SetRenderTranslation(ScreenPosition);
		}
	}
}
