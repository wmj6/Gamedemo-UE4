// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"

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
}

void ASAICharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if(AIC)
	{
		UBlackboardComponent* BlackboardComp =  AIC->GetBlackboardComponent();
		BlackboardComp->SetValueAsObject("Target",Pawn);
	}
}

