// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDeathState.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "LegendPlayerAnim.h"

UPlayerDeathState::UPlayerDeathState()
{

}

void UPlayerDeathState::BeginState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	player->PlayAnimMontage(playerAnim->getHitMontage, player->speed, "PlayerDeath");

	player->SetCollision(FName(TEXT("Death")));
}

void UPlayerDeathState::UpdateState(float _deltaTime)
{
}

void UPlayerDeathState::EndState()
{
}
