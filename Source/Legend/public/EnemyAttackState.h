// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "EnemyAttackState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyAttackState : public UEnemyBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyAttackState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;
};
