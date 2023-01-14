// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseState.h"
#include "EnemyFSM.h"

UEnemyBaseState::UEnemyBaseState()
{

}

void UEnemyBaseState::InitState(UEnemyFSM* _fsm)
{
	fsm = _fsm;
}

void UEnemyBaseState::BeginState()
{

}

void UEnemyBaseState::UpdateState(float _deltaTime)
{
}

void UEnemyBaseState::EndState()
{
}

void UEnemyBaseState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
}
