// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseState.h"
#include "EnemyDeathState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyDeathState : public UEnemyBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyDeathState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

public:
	void ReturnObject();

private:
	FTimerHandle returnTimerHandle;
};
