// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyIdleState.h"
#include "EnemyFSM.h"
#include "Enemy.h"

UEnemyIdleState::UEnemyIdleState()
{
	RegisterFlag((1 << static_cast<uint32>(EEnemyState::IDLE))
		| (1 << static_cast<uint32>(EEnemyState::CHASE))
		| (1 << static_cast<uint32>(EEnemyState::ATTACK))
		| (1 << static_cast<uint32>(EEnemyState::GET_HIT))
		| (1 << static_cast<uint32>(EEnemyState::DEATH)));
}

void UEnemyIdleState::BeginState()
{
	accelerateTime = 0.0f;
}

void UEnemyIdleState::UpdateState(float _deltaTime)
{
	accelerateTime += _deltaTime;
	if (accelerateTime >= idleDelay)
	{
		UEnemyFSM* enemyFSM = GetEnemyFSM();
		enemyFSM->ChangeState(EEnemyState::CHASE);
	}
}

void UEnemyIdleState::EndState()
{
	accelerateTime = 0.0f;
}
