// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "EnemyIdleState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyIdleState : public UEnemyBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyIdleState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

private:
	float idleDelay = 0.1f;
	float accelerateTime = 0.0f;
};
