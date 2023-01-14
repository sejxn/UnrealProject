// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseState.h"
#include "PlayerBaseState.generated.h"

class UPlayerFSM;

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerBaseState : public UBaseState
{
	GENERATED_BODY()

public:
	UPlayerBaseState();

public:
	void InitState(UPlayerFSM* _fsm);
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) override;

public:
	FVector DirectionToCursor();

	UPlayerFSM* GetPlayerFSM() { return fsm; }

private:
	UPlayerFSM* fsm;
};
