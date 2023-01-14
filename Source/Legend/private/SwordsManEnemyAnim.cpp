// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordsManEnemyAnim.h"
#include "SwordsManEnemy.h"
#include "Animation/AnimMontage.h"

USwordsManEnemyAnim::USwordsManEnemyAnim()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempAttackMontage(TEXT("AnimMontage'/Game/Character/Enemy/AISwordsMan/AM_SwordsManEnemyAttack.AM_SwordsManEnemyAttack'"));
	if (tempAttackMontage.Succeeded())
	{
		attackMontage = tempAttackMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempDeathMontage(TEXT("AnimMontage'/Game/Character/Enemy/AISwordsMan/AM_DeathMontage.AM_DeathMontage'"));
	if (tempDeathMontage.Succeeded())
	{
		deathMontage = tempDeathMontage.Object;
	}
}

void USwordsManEnemyAnim::NativeUpdateAnimation(float _deltaSeconds)
{
	Super::NativeUpdateAnimation(_deltaSeconds);

	auto ownerPawn = TryGetPawnOwner();
	auto enemy = Cast<ASwordsManEnemy>(ownerPawn);
	if (enemy)
	{
		FVector velocity = enemy->GetVelocity();
		speed = velocity.Size();
	}
}
