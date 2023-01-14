// Fill out your copyright notice in the Description page of Project Settings.


#include "LegendPlayerAnim.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "Animation/AnimMontage.h"

ULegendPlayerAnim::ULegendPlayerAnim()
{
	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempAttackMontage(TEXT("AnimMontage'/Game/Character/Player/AM_PlayerAttack.AM_PlayerAttack'"));
	if (tempAttackMontage.Succeeded())
	{
		attackMontage = tempAttackMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempGetHitMontage(TEXT("AnimMontage'/Game/Character/Player/AM_PlayerGetHit.AM_PlayerGetHit'"));
	if (tempGetHitMontage.Succeeded())
	{
		getHitMontage = tempGetHitMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempDashMontage(TEXT("AnimMontage'/Game/Character/Player/AM_PlayerDash.AM_PlayerDash'"));
	if (tempDashMontage.Succeeded())
	{
		dashMontage = tempDashMontage.Object;
	}

	const ConstructorHelpers::FObjectFinder<UAnimMontage>
		tempSkillMontage(TEXT("AnimMontage'/Game/Character/Player/AM_PlayerSkill.AM_PlayerSkill'"));
	if (tempSkillMontage.Succeeded())
	{
		skillMontage = tempSkillMontage.Object;
	}
}

void ULegendPlayerAnim::NativeUpdateAnimation(float _deltaSeconds)
{
	Super::NativeUpdateAnimation(_deltaSeconds);
	
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<ALegendPlayer>(ownerPawn);
	if (player)
	{
		FVector velocity = player->GetVelocity();
		if (player->playerFSM)
		{
			EPlayerState playerCurrentState = player->playerFSM->GetCurrentState();
			if (EPlayerState::IDLE_N_RUN != playerCurrentState)
				speed = 0.0f;
			else
				speed = velocity.Size();
		}
	}
}
