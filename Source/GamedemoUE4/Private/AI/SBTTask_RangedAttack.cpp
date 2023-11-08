// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	AAIController* AIController = OwnerComp.GetAIOwner();
	if(ensure(AIController))
	{
		ACharacter* mypawn = Cast<ACharacter>(AIController->GetPawn());
		AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
		if(!mypawn || !Target || !USAttributeComponent::IsActorAlive(Target))
		{
			return EBTNodeResult::Failed;
		}
		
		const FVector MuzzleLocation = mypawn->GetMesh()->GetSocketLocation("Muzzle_01");
	
		const FVector Direction = Target->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();
		
		MuzzleRotation.Pitch += FMath::RandRange(-AimOffset,AimOffset);
		MuzzleRotation.Yaw += FMath::RandRange(-AimOffset,AimOffset);
		
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = Cast<APawn>(mypawn);
		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation,MuzzleRotation,Params);
		return Projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
