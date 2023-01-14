// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordsManEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

ASwordsManEnemyController::ASwordsManEnemyController()
{
	const ConstructorHelpers::FObjectFinder<UBehaviorTree>
		tempBT(TEXT("BehaviorTree'/Game/Character/Enemy/AISwordsMan/BT_SwordsManEnemyAI.BT_SwordsManEnemyAI'"));
	if (tempBT.Succeeded())
	{
		behaviorTree = tempBT.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBlackboardData>
		tempBB(TEXT("BlackboardData'/Game/Character/Enemy/AISwordsMan/BB_SwordsManEnemyAI.BB_SwordsManEnemyAI'"));
	if (tempBB.Succeeded())
	{
		blackboardData = tempBB.Object;
	}
}

void ASwordsManEnemyController::BeginPlay()
{
	Super::BeginPlay();

}
