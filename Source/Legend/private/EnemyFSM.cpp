// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFSM.h"
#include "Kismet/GameplayStatics.h"
#include "LegendPlayer.h"
#include "EnemyIdleState.h"
#include "EnemyChaseState.h"
#include "EnemyAttackState.h"
#include "EnemyGetHitState.h"
#include "EnemyDeathState.h"

void UEnemyFSM::BeginPlay()
{
	Super::BeginPlay();

	ChangeState(EEnemyState::IDLE);
	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ALegendPlayer::StaticClass());
	auto player = Cast<ALegendPlayer>(actor);
	if (player)
		target = player;
}

void UEnemyFSM::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	UBaseState* currentEnemyState = GetBaseState();
	if (enemyState != EEnemyState::NONE && currentEnemyState)
		currentEnemyState->UpdateState(_deltaTime);
}

void UEnemyFSM::InitializeComponent()
{
	Super::InitializeComponent();

	auto idleState = NewObject<UEnemyIdleState>(UEnemyIdleState::StaticClass());
	idleState->InitState(this);
	auto chaseState = NewObject<UEnemyChaseState>(UEnemyChaseState::StaticClass());
	chaseState->InitState(this);
	auto attackState = NewObject<UEnemyAttackState>(UEnemyAttackState::StaticClass());
	attackState->InitState(this);
	auto getHitState = NewObject<UEnemyGetHitState>(UEnemyGetHitState::StaticClass());
	getHitState->InitState(this);
	auto deathState = NewObject<UEnemyDeathState>(UEnemyDeathState::StaticClass());
	deathState->InitState(this);
	PushState(idleState);
	PushState(chaseState);
	PushState(attackState);
	PushState(getHitState);
	PushState(deathState);
}

bool UEnemyFSM::ChangeState(EEnemyState _enemyState)
{
	UBaseState* currentEnemyState = GetBaseState();
	if (nullptr == currentEnemyState)
	{
		currentEnemyState = states[static_cast<uint32>(_enemyState)];
		currentEnemyState->BeginState();
		enemyState = _enemyState;
		SetBaseState(currentEnemyState);
		return true;
	}
	else if (currentEnemyState->CanChangeState(static_cast<uint32>(_enemyState)))
	{
		currentEnemyState->EndState();
		currentEnemyState = states[static_cast<uint32>(_enemyState)];
		currentEnemyState->BeginState();
		enemyState = _enemyState;
		SetBaseState(currentEnemyState);
		return true;
	}
	else
		return true;
}
