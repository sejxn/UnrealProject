// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "EnemyGetHitState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyGetHitState : public UEnemyBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyGetHitState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;
};
