// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterEnemyAnim.h"
#include "FighterEnemy.h"
#include "Animation/AnimMontage.h"

UFighterEnemyAnim::UFighterEnemyAnim()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempAttackMontage(TEXT("AnimMontage'/Game/Character/Enemy/AIFighter/AM_FighterAttack.AM_FighterAttack'"));
	if (tempAttackMontage.Succeeded())
	{
		attackMontage = tempAttackMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempDeathMontage(TEXT("AnimMontage'/Game/Character/Enemy/AIFighter/AM_DeathMontage.AM_DeathMontage'"));
	if (tempDeathMontage.Succeeded())
	{
		deathMontage = tempDeathMontage.Object;
	}
}

void UFighterEnemyAnim::NativeUpdateAnimation(float _deltaSeconds)
{
	Super::NativeUpdateAnimation(_deltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto enemy = Cast<AFighterEnemy>(ownerPawn);
	if (enemy)
	{
		FVector velocity = enemy->GetVelocity();
		speed = velocity.Size();
	}
}
