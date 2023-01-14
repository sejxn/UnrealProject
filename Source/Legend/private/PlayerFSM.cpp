// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFSM.h"
#include "PlayerIdleNRunState.h"
#include "PlayerAttackState.h"
#include "PlayerGetHitState.h"
#include "PlayerDashState.h"
#include "PlayerUpperAttackState.h"
#include "PlayerSlashAttackState.h"
#include "PlayerFlyingAttackState.h"
#include "PlayerCrashAttackState.h"
#include "PlayerBlockState.h"
#include "PlayerParryState.h"
#include "PlayerParryAttackState.h"
#include "PlayerDeathState.h"

void UPlayerFSM::BeginPlay()
{
	Super::BeginPlay();

	UBaseState* currentPlayerState = GetBaseState();
	currentPlayerState = states[static_cast<uint32>(EPlayerState::IDLE_N_RUN)];
	currentPlayerState->BeginState();
	playerCurrentState = EPlayerState::IDLE_N_RUN;
	SetBaseState(currentPlayerState);
}

void UPlayerFSM::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	UBaseState* currentPlayerState = GetBaseState();
	if (playerCurrentState != EPlayerState::NONE && currentPlayerState)
		currentPlayerState->UpdateState(_deltaTime);
}

void UPlayerFSM::InitializeComponent()
{
	Super::InitializeComponent();

	auto idleNRunState = NewObject<UPlayerIdleNRunState>(UPlayerIdleNRunState::StaticClass());
	idleNRunState->InitState(this);
	auto attackState = NewObject<UPlayerAttackState>(UPlayerAttackState::StaticClass());
	attackState->InitState(this);
	auto getHitState = NewObject<UPlayerGetHitState>(UPlayerGetHitState::StaticClass());
	getHitState->InitState(this);
	auto dashState = NewObject<UPlayerDashState>(UPlayerDashState::StaticClass());
	dashState->InitState(this);
	auto upperAttackState = NewObject<UPlayerUpperAttackState>(UPlayerUpperAttackState::StaticClass());
	upperAttackState->InitState(this);
	auto slashAttackState = NewObject<UPlayerSlashAttackState>(UPlayerSlashAttackState::StaticClass());
	slashAttackState->InitState(this);
	auto flyingAttackState = NewObject<UPlayerFlyingAttackState>(UPlayerFlyingAttackState::StaticClass());
	flyingAttackState->InitState(this);
	auto crashAttackState = NewObject<UPlayerCrashAttackState>(UPlayerCrashAttackState::StaticClass());
	crashAttackState->InitState(this);
	auto blockState = NewObject<UPlayerBlockState>(UPlayerBlockState::StaticClass());
	blockState->InitState(this);
	auto parryState = NewObject<UPlayerParryState>(UPlayerParryState::StaticClass());
	parryState->InitState(this);
	auto parryAttackState = NewObject<UPlayerParryAttackState>(UPlayerParryAttackState::StaticClass());
	parryAttackState->InitState(this);
	auto deathState = NewObject<UPlayerDeathState>(UPlayerDeathState::StaticClass());
	deathState->InitState(this);
	PushState(idleNRunState);
	PushState(attackState);
	PushState(getHitState);
	PushState(dashState);
	PushState(upperAttackState);
	PushState(slashAttackState);
	PushState(flyingAttackState);
	PushState(crashAttackState);
	PushState(blockState);
	PushState(parryState);
	PushState(parryAttackState);
	PushState(deathState);
}

bool UPlayerFSM::ChangeState(EPlayerState _playerState)
{
	UBaseState* currentPlayerState = GetBaseState();

	if (!currentPlayerState)
		return false;

	if (currentPlayerState->CanChangeState(static_cast<uint32>(_playerState)))
	{
		currentPlayerState->EndState();
		currentPlayerState = states[static_cast<uint32>(_playerState)];
		currentPlayerState->BeginState();
		playerCurrentState = _playerState;
		SetBaseState(currentPlayerState);
		return true;
	}
	else
		return false;
}
