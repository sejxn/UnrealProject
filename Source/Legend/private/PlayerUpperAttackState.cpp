// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUpperAttackState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "LegendPlayerAnim.h"

UPlayerUpperAttackState::UPlayerUpperAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerUpperAttackState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	// ¸ùÅ¸ÁÖ
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->skillMontage, player->speed, "UpperAttack");

	FVector moveDir = DirectionToCursor();

	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerUpperAttackState::UpdateState(float _deltaTime)
{
	
}

void UPlayerUpperAttackState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
}

void UPlayerUpperAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("QButton", IE_Pressed, this,
		&UPlayerUpperAttackState::AttackPressed);
}

void UPlayerUpperAttackState::AttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::UPPER_ATTACK);
}
