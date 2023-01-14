// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterEnemyController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AFighterEnemyController::AFighterEnemyController()
{
	const ConstructorHelpers::FObjectFinder<UBehaviorTree>
		tempBT(TEXT("BehaviorTree'/Game/Character/Enemy/AIFighter/BT_FighterEnemyAI.BT_FighterEnemyAI'"));
	if (tempBT.Succeeded())
	{
		behaviorTree = tempBT.Object;
	}

	const ConstructorHelpers::FObjectFinder<UBlackboardData>
		tempBB(TEXT("BlackboardData'/Game/Character/Enemy/AIFighter/BB_FighterEnemyAI.BB_FighterEnemyAI'"));
	if (tempBB.Succeeded())
	{
		blackboardData = tempBB.Object;
	}
}

void AFighterEnemyController::BeginPlay()
{
	Super::BeginPlay();

}