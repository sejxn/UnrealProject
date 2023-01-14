// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDashState.h"
#include "LegendPlayer.h"
#include "PlayerFSM.h"
#include "LegendPlayerAnim.h"

UPlayerDashState::UPlayerDashState()
{
    RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
        | (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerDashState::BeginState()
{
    UPlayerFSM* playerFSM = GetPlayerFSM();
    ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

    // 몽타주
    ULegendPlayerAnim* playerAnim = Cast<ULegendPlayerAnim>(playerFSM->GetAnim());
    player->PlayAnimMontage(playerAnim->dashMontage, player->speed, "Dash0");

    // 콜리젼
    player->SetCollision(FName(TEXT("PlayerDash")));

    FVector moveDir = DirectionToCursor();
    
    player->SetActorRotation(FRotator(0.0f, moveDir.ToOrientationRotator().Yaw, 0.0f));
}

void UPlayerDashState::UpdateState(float _deltaTime)
{
    
}

void UPlayerDashState::EndState()
{   
    UPlayerFSM* playerFSM = GetPlayerFSM();
    ALegendPlayer* player = Cast<ALegendPlayer>(playerFSM->GetOwner());

    player->StopAnimMontage();

    player->SetCollision(FName(TEXT("Player")));
}

void UPlayerDashState::SetupInputBinding(UInputComponent* _playerInputComponent)
{
    _playerInputComponent->BindAction("SpaceBar", IE_Pressed, this,
        &UPlayerDashState::DashPressed);
}

void UPlayerDashState::DashPressed()
{
    UPlayerFSM* playerFSM = GetPlayerFSM();
    playerFSM->ChangeState(EPlayerState::DASH);
}
