// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIAttackTask.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class LEGEND_API UAIAttackTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UAIAttackTask();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory, float _deltaSeconds) override;
};
