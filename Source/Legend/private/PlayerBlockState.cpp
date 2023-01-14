// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBlockState.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "LegendPlayerAnim.h"

UPlayerBlockState::UPlayerBlockState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::GET_HIT))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::PARRY))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerBlockState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->getHitMontage, 1.0f, "Block");

	FVector moveDir = DirectionToCursor();
	player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerBlockState::UpdateState(float _deltaTime)
{
}

void UPlayerBlockState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
}

void UPlayerBlockState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("SButton", IE_Pressed, this,
		&UPlayerBlockState::BlockPressed);
}

void UPlayerBlockState::BlockPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->ChangeState(EPlayerState::BLOCK);
}
