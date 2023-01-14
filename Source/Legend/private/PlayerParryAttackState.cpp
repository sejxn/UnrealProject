// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerParryAttackState.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "LegendPlayerAnim.h"

UPlayerParryAttackState::UPlayerParryAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerParryAttackState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->skillMontage, 1.0f, "ParryAttack");

	// ÄÝ¸®Á¯
	player->SetCollision(FName(TEXT("PlayerDash")));

	FVector moveDir = DirectionToCursor();
	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerParryAttackState::UpdateState(float _deltaTime)
{
}

void UPlayerParryAttackState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	player->StopAnimMontage();

	player->SetCollision(FName(TEXT("Player")));
}

void UPlayerParryAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("SButton", IE_Pressed, this,
		&UPlayerParryAttackState::ParryAttackPressed);
}

void UPlayerParryAttackState::ParryAttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::PARRY_ATTACK);
}
