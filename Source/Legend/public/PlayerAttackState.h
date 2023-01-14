// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerAttackState.generated.h"

UENUM(BlueprintType)
enum class EAttackState : uint8
{
	IDLE,
	FIRST_ATTACK,
	SECOND_ATTACK,
	THIRD_ATTACK,
	END,
};

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerAttackState : public UPlayerBaseState
{
	GENERATED_BODY()
	
public:
	UPlayerAttackState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) override;

	void AttackPressed();

private:
	void RotationToCursor(float _deltaTime);

private:
	EAttackState currentAttackState = EAttackState::IDLE;
	FVector moveDir = FVector(0.0f);
};
