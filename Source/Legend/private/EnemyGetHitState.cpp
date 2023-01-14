// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGetHitState.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"

UEnemyGetHitState::UEnemyGetHitState()
{
	RegisterFlag((1 << static_cast<uint32>(EEnemyState::IDLE))
		| (1 << static_cast<uint32>(EEnemyState::GET_HIT))
		| (1 << static_cast<uint32>(EEnemyState::DEATH)));
}

void UEnemyGetHitState::BeginState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AEnemy* enemy = Cast<AEnemy>(enemyFSM->GetOwner());
	UEnemyAnim* enemyAnim = Cast<UEnemyAnim>(enemyFSM->GetAnim());
	enemy->PlayAnimMontage(enemyAnim->getHitMontage, enemy->speed, "GetHit0");
}

void UEnemyGetHitState::UpdateState(float _deltaTime)
{
	
}

void UEnemyGetHitState::EndState()
{
	
}
