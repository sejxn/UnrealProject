// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerIdleNRunState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerIdleNRunState : public UPlayerBaseState
{
	GENERATED_BODY()
	
public:
	UPlayerIdleNRunState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) override;

	void RMousePressed();
	void RMouseReleased();

	void Move();

private:
	bool bRMousePressed = false;
};
