// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyController::AEnemyController()
{
	
}

void AEnemyController::RunAI()
{
	if (UseBlackboard(blackboardData, Blackboard))
	{
		Blackboard->SetValueAsBool(FName(TEXT("IsDeadKey")), false);

		RunBehaviorTree(behaviorTree);
	}
}

void AEnemyController::StopAI()
{
	UBehaviorTreeComponent* behaviorTreeComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent());
	if (nullptr == behaviorTreeComponent) return;
	
	behaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
