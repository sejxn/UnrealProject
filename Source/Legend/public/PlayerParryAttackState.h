// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerParryAttackState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerParryAttackState : public UPlayerBaseState
{
	GENERATED_BODY()
	
public:
	UPlayerParryAttackState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) override;

public:
	void ParryAttackPressed();
};
