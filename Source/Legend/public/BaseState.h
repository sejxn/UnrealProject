// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/InputComponent.h"
#include "BaseState.generated.h"

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	IDLE_N_RUN,
	ATTACK,
	GET_HIT,
	DASH,
	UPPER_ATTACK,
	SLASH_ATTACK,
	FLYING_ATTACK,
	CRASH_ATTACK,
	BLOCK,
	PARRY,
	PARRY_ATTACK,
	DEATH,
	NONE,
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	IDLE,
	CHASE,
	ATTACK,
	GET_HIT,
	DEATH,
	NONE,
};

/**
 * 
 */
UCLASS(abstract)
class LEGEND_API UBaseState : public UObject
{
	GENERATED_BODY()

public:
	UBaseState() {}

public:
	virtual void BeginState() PURE_VIRTUAL(UBaseState::BeginState, );
	virtual void UpdateState(float _deltaTime) PURE_VIRTUAL(UBaseState::UpdateState, );
	virtual void EndState() PURE_VIRTUAL(UBaseState::EndState, );

	virtual void SetupInputBinding(UInputComponent* _playerInputComponent) {};

	void RegisterFlag(uint32 _stateFlag);
	bool CanChangeState(uint32 _state);

private:
	uint32 canChangeStateFlag = 0; // 비트 플래그. 1이면 변경 가능.
};
