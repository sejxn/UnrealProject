// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyChaseState.h"
#include "EnemyFSM.h"
#include "LegendPlayer.h"
#include "GameFramework/Controller.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UEnemyChaseState::UEnemyChaseState()
{
	RegisterFlag((1 << static_cast<uint32>(EEnemyState::IDLE))
		| (1 << static_cast<uint32>(EEnemyState::ATTACK))
		| (1 << static_cast<uint32>(EEnemyState::GET_HIT))
		| (1 << static_cast<uint32>(EEnemyState::DEATH)));
}

void UEnemyChaseState::BeginState()
{

}

void UEnemyChaseState::UpdateState(float _deltaTime)
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	ALegendPlayer* playerTarget = enemyFSM->GetTarget();
	if (playerTarget)
	{
		FVector targetLocation = playerTarget->GetActorLocation();
		AController* enemyController = enemyFSM->GetController();
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(enemyController, targetLocation);
	
		FVector myLocation = enemyFSM->GetOwner()->GetActorLocation();
		FVector distance = targetLocation - myLocation;
		if (distance.Size() <= enemyFSM->GetOwnerCharacter()->attackDist && RotationToTarget(_deltaTime))
		{
			enemyFSM->ChangeState(EEnemyState::ATTACK);
		}
	}
}

void UEnemyChaseState::EndState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AController* enemyController = enemyFSM->GetController();
	enemyController->StopMovement();
}

bool UEnemyChaseState::RotationToTarget(float _deltaTime)
{
	// �÷��̾�� ȸ���� �Ѵ�. ȸ�� �� �ϸ� true, �ƴϸ� false
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	ALegendPlayer* playerTarget = enemyFSM->GetTarget();
	AActor* myActor = enemyFSM->GetOwner();
	if (playerTarget)
	{
		FVector targetLocation = playerTarget->GetActorLocation();
		FVector myLocation = myActor->GetActorLocation();
		FVector distVec = targetLocation - myLocation;
		FVector norDistVec = distVec.GetSafeNormal();

		FVector rightVector = myActor->GetActorRightVector();
		FVector forwardVector = myActor->GetActorForwardVector();

		// ���� �� ���ͻ����� ������ 1�� �����ٸ�(0��) ȸ������ ����
		float parallel = FVector::DotProduct(forwardVector, norDistVec);
		if (parallel <= 0.99f)
		{
			float dir = FVector::DotProduct(rightVector, norDistVec);
			// 0 �̻��̸� ������
			dir = dir >= 0.0f ? 1 : -1;

			FRotator deltaRot = FRotator(0.0f, _deltaTime * attackRotationRate * dir, 0.0f);
			myActor->AddActorWorldRotation(deltaRot.Quaternion());
			return false;
		}
		else
			return true;
	}

	return false;
}
