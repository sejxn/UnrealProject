// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSlashAttackState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "LegendPlayerAnim.h"

UPlayerSlashAttackState::UPlayerSlashAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerSlashAttackState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	// ¸ùÅ¸ÁÖ
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->skillMontage, player->speed, "SlashAttack");

	FVector moveDir = DirectionToCursor();

	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerSlashAttackState::UpdateState(float _deltaTime)
{
	
}

void UPlayerSlashAttackState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
}

void UPlayerSlashAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("WButton", IE_Pressed, this,
		&UPlayerSlashAttackState::AttackPressed);
}

void UPlayerSlashAttackState::AttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::SLASH_ATTACK);
}
