// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCrashAttackState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "LegendPlayerAnim.h"

UPlayerCrashAttackState::UPlayerCrashAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerCrashAttackState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	// 몽타주
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->skillMontage, player->speed, "CrashAttack");

	// 콜리젼
	player->SetCollision(FName(TEXT("PlayerMovingAttack")));

	FVector moveDir = DirectionToCursor();

	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerCrashAttackState::UpdateState(float _deltaTime)
{
	
}

void UPlayerCrashAttackState::EndState()
{	
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	player->StopAnimMontage();

	player->SetCollision(FName(TEXT("Player")));
}

void UPlayerCrashAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("RButton", IE_Pressed, this,
		&UPlayerCrashAttackState::AttackPressed);
}

void UPlayerCrashAttackState::AttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::CRASH_ATTACK);
}
