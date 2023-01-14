// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackState.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"

UEnemyAttackState::UEnemyAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EEnemyState::IDLE))
		| (1 << static_cast<uint32>(EEnemyState::CHASE))
		| (1 << static_cast<uint32>(EEnemyState::ATTACK))
		| (1 << static_cast<uint32>(EEnemyState::GET_HIT))
		| (1 << static_cast<uint32>(EEnemyState::DEATH)));
}

void UEnemyAttackState::BeginState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AEnemy* enemy = Cast<AEnemy>(enemyFSM->GetOwner());
	UEnemyAnim* enemyAnim = Cast<UEnemyAnim>(enemyFSM->GetAnim());
	enemy->PlayAnimMontage(enemyAnim->attackMontage, enemy->speed, "Attack0");
}

void UEnemyAttackState::UpdateState(float _deltaTime)
{
	
}

void UEnemyAttackState::EndState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	enemyFSM->GetOwnerCharacter()->StopAnimMontage();
}
