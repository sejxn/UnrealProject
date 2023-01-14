// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerParryState.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "LegendPlayerAnim.h"

UPlayerParryState::UPlayerParryState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::PARRY_ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerParryState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->getHitMontage, 1.0f, "Parry");
}

void UPlayerParryState::UpdateState(float _deltaTime)
{
}

void UPlayerParryState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
}

void UPlayerParryState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("SButton", IE_Pressed, this,
		&UPlayerParryState::ParryPressed);
}

void UPlayerParryState::ParryPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::PARRY_ATTACK);
}
