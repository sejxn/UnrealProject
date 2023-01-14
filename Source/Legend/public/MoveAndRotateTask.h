// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MoveAndRotateTask.generated.h"

class ABaseCharacter;

/**
 * 
 */
UCLASS(Blueprintable)
class LEGEND_API UMoveAndRotateTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UMoveAndRotateTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& _ownerComp,
		uint8* _nodeMemory, float _deltaSeconds) override;

	virtual void OnTaskFinished(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory, EBTNodeResult::Type _taskResult) override;

private:
	bool MoveToPlayer(UBehaviorTreeComponent& _ownerComp, AActor* _playerActor, ABaseCharacter* _myActor);
	bool RotateToPlayer(UBehaviorTreeComponent& _ownerComp, float _deltaSeconds, AActor* _playerActor, ABaseCharacter* _myActor);

private:
	float attackRotationRate = 360.0f;
};
