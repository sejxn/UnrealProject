// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerIdleNRunState.h"
#include "PlayerFSM.h"
#include "LegendPlayer.h"
#include "GameFramework/PlayerController.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>

UPlayerIdleNRunState::UPlayerIdleNRunState()
{
	RegisterFlag((1 << static_cast<uint32>(EPlayerState::IDLE_N_RUN))
		| (1 << static_cast<uint32>(EPlayerState::ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::GET_HIT))
		| (1 << static_cast<uint32>(EPlayerState::DASH))
		| (1 << static_cast<uint32>(EPlayerState::UPPER_ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::SLASH_ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::FLYING_ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::CRASH_ATTACK))
		| (1 << static_cast<uint32>(EPlayerState::BLOCK))
		| (1 << static_cast<uint32>(EPlayerState::DEATH)));
}

void UPlayerIdleNRunState::BeginState()
{
	
}

void UPlayerIdleNRunState::UpdateState(float _deltaTime)
{
	Move();
}

void UPlayerIdleNRunState::EndState()
{
	UPlayerFSM* playerFSM = GetPlayerFSM();
	AController* playerController = playerFSM->GetController();
	playerController->StopMovement();
}

void UPlayerIdleNRunState::SetupInputBinding(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("RightMouseClick", IE_Pressed, this,
		&UPlayerIdleNRunState::RMousePressed);
	PlayerInputComponent->BindAction("RightMouseClick", IE_Released, this,
		&UPlayerIdleNRunState::RMouseReleased);
}

void UPlayerIdleNRunState::RMousePressed()
{
	bRMousePressed = true;
}

void UPlayerIdleNRunState::RMouseReleased()
{
	bRMousePressed = false;
}

void UPlayerIdleNRunState::Move()
{
	if (bRMousePressed)
	{
		FHitResult Hit;
		UPlayerFSM* playerFSM = GetPlayerFSM();
		APlayerController* playerController = Cast<APlayerController>(playerFSM->GetController());
		playerController->GetHitResultUnderCursor(ECC_GameTraceChannel1, false, Hit);

		if (Hit.bBlockingHit)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(playerController, Hit.ImpactPoint);
		}
	}
}
