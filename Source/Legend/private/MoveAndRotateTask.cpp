// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveAndRotateTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "BaseCharacter.h"
#include "FighterEnemy.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UMoveAndRotateTask::UMoveAndRotateTask()
{
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UMoveAndRotateTask::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	Super::ExecuteTask(_ownerComp, _nodeMemory);

	return EBTNodeResult::Type::InProgress;
}

void UMoveAndRotateTask::TickTask(UBehaviorTreeComponent& _ownerComp,
	uint8* _nodeMemory, float _deltaSeconds)
{
	Super::TickTask(_ownerComp, _nodeMemory, _deltaSeconds);

	UObject* playerObj = _ownerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("PlayerKey")));
	if (!playerObj)
		FinishLatentTask(_ownerComp, EBTNodeResult::Type::Failed);

	AActor* playerActor = Cast<AActor>(playerObj);
	ABaseCharacter* myActor = Cast<ABaseCharacter>(_ownerComp.GetAIOwner()->GetPawn());
	if (!playerActor || !myActor)
		FinishLatentTask(_ownerComp, EBTNodeResult::Type::Failed);
	
	if(!MoveToPlayer(_ownerComp, playerActor, myActor) && !RotateToPlayer(_ownerComp, _deltaSeconds, playerActor, myActor))
		FinishLatentTask(_ownerComp, EBTNodeResult::Type::Succeeded);
}

void UMoveAndRotateTask::OnTaskFinished(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory, EBTNodeResult::Type _taskResult)
{
	AController* myController = _ownerComp.GetAIOwner();
	myController->StopMovement();
}

bool UMoveAndRotateTask::MoveToPlayer(UBehaviorTreeComponent& _ownerComp, AActor* _playerActor, ABaseCharacter* _myActor)
{
	FVector playerLocation = _playerActor->GetActorLocation();
	AController* myController = _ownerComp.GetAIOwner();
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(myController, playerLocation);

	FVector myLocation = _myActor->GetActorLocation();
	FVector toPlayerVec = playerLocation - myLocation;

	if (toPlayerVec.Size() <= _myActor->attackDist)
		return false;		

	return true;
}

bool UMoveAndRotateTask::RotateToPlayer(UBehaviorTreeComponent& _ownerComp, float _deltaSeconds, AActor* _playerActor, ABaseCharacter* _myActor)
{
	FVector playerLocation = _playerActor->GetActorLocation();
	FVector myLocation = _myActor->GetActorLocation();

	FVector toPlayerVec = playerLocation - myLocation;
	toPlayerVec = toPlayerVec.GetSafeNormal();
	FVector forwardVec = _myActor->GetActorForwardVector();
	forwardVec = forwardVec.GetSafeNormal();
	FVector rightVec = _myActor->GetActorRightVector();
	rightVec = rightVec.GetSafeNormal();

	float parallel = FVector::DotProduct(forwardVec, toPlayerVec);
	if (parallel <= 0.99f)
	{
		float dir = FVector::DotProduct(rightVec, toPlayerVec);
		// 0 이상이면 오른쪽
		dir = dir >= 0.0f ? 1 : -1;

		FRotator deltaRot = FRotator(0.0f, _deltaSeconds * attackRotationRate * dir, 0.0f);
		_myActor->AddActorWorldRotation(deltaRot.Quaternion());
		return true;
	}
	else
		return false;

	return true;
}
