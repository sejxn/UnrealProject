// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnim.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "Animation/AnimMontage.h"

UEnemyAnim::UEnemyAnim()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempAttackMontage(TEXT("AnimMontage'/Game/Character/Enemy/Zombie/AM_EnemyAttack.AM_EnemyAttack'"));
	if (tempAttackMontage.Succeeded())
	{
		attackMontage = tempAttackMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempGetHitMontage(TEXT("AnimMontage'/Game/Character/Enemy/Zombie/AM_EnemyGetHit.AM_EnemyGetHit'"));
	if (tempGetHitMontage.Succeeded())
	{
		getHitMontage = tempGetHitMontage.Object;
	}
}

void UEnemyAnim::NativeUpdateAnimation(float _deltaSeconds)
{
	Super::NativeUpdateAnimation(_deltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto enemy = Cast<AEnemy>(ownerPawn);
	if (enemy)
	{
		FVector velocity = enemy->GetVelocity();
		speed = velocity.Size();
		if (enemy->enemyFSM)
			enemyState = enemy->enemyFSM->enemyState;
	}
}
