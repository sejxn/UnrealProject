// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

class UBehaviorTree;
class UBlackboardData;

/**
 * 
 */
UCLASS()
class LEGEND_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyController();

public:
	void RunAI();
	void StopAI();

public:
	UPROPERTY(VisibleAnywhere, Category = BehaviorTree)
	UBehaviorTree* behaviorTree;

	UPROPERTY(VisibleAnywhere, Category = BehaviorTree)
	UBlackboardData* blackboardData;
};
