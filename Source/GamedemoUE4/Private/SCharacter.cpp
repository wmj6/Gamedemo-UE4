// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"

#include "SActionComponent.h"
#include "SAttributeComponent.h"
#include "SInteractionComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>(TEXT("InteractionComp"));

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	ActionComp = CreateDefaultSubobject<USActionComponent>(TEXT("ActionComp"));
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this,&ASCharacter::OnHealthChanged);
}

FVector ASCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASCharacter::MoveForward(float value)
{
	FRotator controlRotation = GetControlRotation();
	controlRotation.Pitch = 0.0f;
	controlRotation.Roll = 0.0f;
	AddMovementInput(controlRotation.Vector(), value);
}

void ASCharacter::MoveRight(float value)
{
	FRotator controlRotation = GetControlRotation();
	controlRotation.Pitch = 0.0f;
	controlRotation.Roll = 0.0f;
	const FVector rightVector = FRotationMatrix(controlRotation).GetScaledAxis(EAxis::Y);
	AddMovementInput(rightVector, value);
}

void ASCharacter::SecondarySkill()
{
	ActionComp->StartActionByName(this,"ProjectileAttack");
}

void ASCharacter::Interact()
{
	if(!IsValid(InteractionComp))
	{
		UE_LOG(LogTemp,Warning,TEXT("InteractionComp is null pointer"))
		return ;
	}
	InteractionComp->PrimaryInteract();
}

void ASCharacter::PrimarySkill()
{
	ActionComp->StartActionByName(this,"Blackhole");
}

void ASCharacter::SprintStart()
{
	ActionComp->StartActionByName(this,"Sprint");
}

void ASCharacter::SprintStop()
{
	ActionComp->StopActionByName(this,"Sprint");
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth,
                                  float Delta)
{
	GetMesh()->SetScalarParameterValueOnMaterials("Time",GetWorld()->GetTimeSeconds());
	if( NewHealth<=0.0f && Delta<0.0f)
	{
		DisableInput(Cast<APlayerController>(GetController()));
	}
}

// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this,&ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this,&APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("SecondarySkill",IE_Pressed, this,&ASCharacter::SecondarySkill);
	PlayerInputComponent->BindAction("PrimarySkill",IE_Pressed, this,&ASCharacter::PrimarySkill);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ACharacter::Jump);
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ASCharacter::Interact);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ASCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ASCharacter::SprintStop);
}


