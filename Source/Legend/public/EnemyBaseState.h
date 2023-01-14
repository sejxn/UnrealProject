// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "EnemyBaseState.generated.h"

class UEnemyFSM;

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyBaseState : public UBaseState
{
	GENERATED_BODY()
	
public:
	UEnemyBaseState();

public:
	void InitState(UEnemyFSM* _fsm);
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) override;

public:
	UEnemyFSM* GetEnemyFSM() { return fsm; }

private:
	UEnemyFSM* fsm;
};
