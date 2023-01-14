// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "LegendPlayerAnim.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UPlayerAttackState::UPlayerAttackState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
	| (1 << static_cast<uint32>(EPlayerState::GET_HIT))
	| (1 << static_cast<uint32>(EPlayerState::DASH))
	| (1 << static_cast<uint32>(EPlayerState::UPPER_ATTACK))
	| (1 << static_cast<uint32>(EPlayerState::SLASH_ATTACK))
	| (1 << static_cast<uint32>(EPlayerState::FLYING_ATTACK))
	| (1 << static_cast<uint32>(EPlayerState::CRASH_ATTACK))
	| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerAttackState::BeginState()
{
	currentAttackState = EAttackState::IDLE;
}

void UPlayerAttackState::UpdateState(float _deltaTime)
{
	RotationToCursor(_deltaTime);
}

void UPlayerAttackState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	playerFSM->GetOwnerCharacter()->StopAnimMontage();
	currentAttackState = EAttackState::IDLE;
	playerFSM->GetOwnerCharacter()->readyToAttack = true;
	moveDir = FVector(0.0f);
}

void UPlayerAttackState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
	_playerInputComponent->BindAction("AButton", IE_Pressed, this,
		&UPlayerAttackState::AttackPressed);
}

void UPlayerAttackState::AttackPressed()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	EPlayerState playerCurrentState = playerFSM->GetCurrentState();

	if (!playerFSM->GetOwnerCharacter()->readyToAttack)
		return;

	if (EPlayerState::ATTACK != playerCurrentState)
	{
		if (!playerFSM->ChangeState(EPlayerState::ATTACK))
			return;
	}

	ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());
	ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
	int32 attackNum = static_cast<int32>(currentAttackState);
	FString attackString = FString(TEXT("Attack")) + FString::FromInt(attackNum);
	player->PlayAnimMontage(playerAnim->attackMontage, player->speed, FName(*attackString));
	currentAttackState = static_cast<EAttackState>(((attackNum + 1) % static_cast<int32>(EAttackState::END)));
	player->readyToAttack = false;

	moveDir = DirectionToCursor();
}

void UPlayerAttackState::RotationToCursor(float _deltaTime)
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	AActor* myActor = playerFSM->GetOwner();

	FVector rightVector = myActor->GetActorRightVector();
	FVector forwardVector = myActor->GetActorForwardVector();

	float parallel = FVector::DotProduct(forwardVector, moveDir);
	if (parallel <= 0.99f)
	{
		float dir = FVector::DotProduct(rightVector, moveDir);
		// 0 이상이면 오른쪽
		dir = dir >= 0.0f ? 1 : -1;

		FRotator deltaRot = FRotator(0.0f, _deltaTime * 480.0f * dir, 0.0f);
		myActor->AddActorWorldRotation(deltaRot.Quaternion());
	}
}
