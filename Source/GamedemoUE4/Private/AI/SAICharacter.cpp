// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BrainComponent.h"
#include "SAttributeComponent.h"
#include "AI/SAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "UMG/SWorldUserWidget.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComp"));
	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ASAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASAICharacter::Tick(float DeltaTime)                                                              
{
	Super::Tick(DeltaTime);

}

void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SensingComp->OnSeePawn.AddDynamic(this,&ASAICharacter::OnSeePawn);
	AttributeComp->OnHealthChanged.AddDynamic(this,&ASAICharacter::OnHealthChange);
}

void ASAICharacter::OnSeePawn(APawn* Pawn)
{
	SetAimTarget(Pawn);
}

void ASAICharacter::OnHealthChange(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	GetMesh()->SetScalarParameterValueOnMaterials("Time",GetWorld()->GetTimeSeconds());
	if(InstigatorActor)
	{
		SetAimTarget(InstigatorActor);
	}
	if(ActiveHealthBarWidget == nullptr)
	{
		if(ensure(HealthBarWidgetClass))
		{
			ActiveHealthBarWidget =  Cast<USWorldUserWidget>(CreateWidget(GetWorld(),HealthBarWidgetClass));
			
			GetWorldTimerManager().SetTimer(TimerHandle_RemoveHealthBar,
				[this]
				{
					ActiveHealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
				},
				1.0f,
				false
			);
			if(ActiveHealthBarWidget)
			{
				ActiveHealthBarWidget->SetAttachedActor(this);
				ActiveHealthBarWidget->AddToViewport();
			}
		}
	}else
	{
		ActiveHealthBarWidget->SetVisibility(ESlateVisibility::Visible);
		GetWorldTimerManager().SetTimer(TimerHandle_RemoveHealthBar,
				[this]
				{
					ActiveHealthBarWidget->SetVisibility(ESlateVisibility::Collapsed);
				},
				1.0f,
				false
			);
	}
	
	
	if( NewHealth<=0.0f && Delta<0.0f)
	{
		ASAIController* AIC = Cast<ASAIController>(GetController());
		if(AIC)
		{
			AIC->GetBrainComponent()->StopLogic("killed");
		}
		GetMesh()->SetAllBodiesSimulatePhysics(true);
		GetMesh()->SetCollisionProfileName("Ragdoll");
		SetLifeSpan(10.0f);
	}
	
}

void ASAICharacter::SetAimTarget(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if(AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("Target",NewTarget);
	}
}

