// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "EnemyChaseState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyChaseState : public UEnemyBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyChaseState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

private:
	bool RotationToTarget(float _deltaTime);

private:
	float attackRotationRate = 360.0f;
};
