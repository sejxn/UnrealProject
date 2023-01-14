// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBaseState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"

UPlayerBaseState::UPlayerBaseState()
{
	
}

void UPlayerBaseState::InitState(UPlayerFSM* _fsm)
{
	fsm = _fsm;
	ALegendPlayer* legendPlayer = Cast<ALegendPlayer>(fsm->GetOwner());
	if (legendPlayer)
		legendPlayer->onInputBindingDelegate.AddUObject(this, &UPlayerBaseState::SetupInputBinding);
}

void UPlayerBaseState::BeginState()
{

}

void UPlayerBaseState::UpdateState(float _deltaTime)
{
}

void UPlayerBaseState::EndState()
{
}

void UPlayerBaseState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
}

FVector UPlayerBaseState::DirectionToCursor()
{
    ALegendPlayer* player = Cast<ALegendPlayer>(fsm->GetOwner());

    // 이동할 방향 지정
    FHitResult Hit;
    APlayerController* playerController = Cast<APlayerController>(player->GetController());
    playerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);

    FVector myLocation = player->GetActorLocation();

    FVector moveDir = Hit.ImpactPoint - myLocation;
    if (!moveDir.Normalize())
    {
        moveDir = player->GetActorForwardVector();
    }
    else
    {
        FVector upVec = player->GetActorUpVector();
        FVector rightVec = FVector::CrossProduct(upVec, moveDir);
        moveDir = FVector::CrossProduct(rightVec, upVec);
        moveDir.Normalize();
    }

    return moveDir;
}
