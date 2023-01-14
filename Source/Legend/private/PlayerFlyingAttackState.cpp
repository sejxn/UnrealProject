// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlyingAttackState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "LegendPlayerAnim.h"

UPlayerFlyingAttackState::UPlayerFlyingAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerFlyingAttackState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	// ¸ùÅ¸ÁÖ
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->skillMontage, player->speed, "FlyingAttack");

	FVector moveDir = DirectionToCursor();

	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerFlyingAttackState::UpdateState(float _deltaTime)
{
	
}

void UPlayerFlyingAttackState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
}

void UPlayerFlyingAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("EButton", IE_Pressed, this,
		&UPlayerFlyingAttackState::AttackPressed);
}

void UPlayerFlyingAttackState::AttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::FLYING_ATTACK);
}
