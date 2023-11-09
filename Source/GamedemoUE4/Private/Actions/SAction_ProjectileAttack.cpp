// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SAction_ProjectileAttack.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	ActionName = "ProjectileAttack";
	HandSocketName = "Muzzle_01";
	AttackAnimDelay = 0.2f;
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
	ACharacter* InstigatorCharacter = Cast<ACharacter>(Instigator);
	if(InstigatorCharacter)
	{
		InstigatorCharacter->PlayAnimMontage(AttackAnim);

		FTimerHandle TimerHandle_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this,"AttackDelay_Elapsed",InstigatorCharacter);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_AttackDelay,Delegate,AttackAnimDelay,false);
	}
}

void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if(ensure(ProjectileClass))
	{
		const FVector FireLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);
		
		FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape shape;
		shape.SetSphere(20.0f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);
		
		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();

		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() *5000);

		FHitResult Hit;
		if(GetWorld()->SweepSingleByObjectType(Hit,TraceStart,TraceEnd,FQuat::Identity,ObjParams,shape,Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}

		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - FireLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, FireLocation);

		GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnTM,SpawnParams);
	}
	StopAction(InstigatorCharacter);
}
