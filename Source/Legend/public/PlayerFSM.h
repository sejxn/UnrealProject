// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFSM.h"
#include "PlayerFSM.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerFSM : public UBaseFSM
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;
	virtual void InitializeComponent() override;

public:
	UFUNCTION(BlueprintCallable, Category = States)
	bool ChangeState(EPlayerState _playerState);

	EPlayerState GetCurrentState() { return playerCurrentState; }

private:
	EPlayerState playerCurrentState = EPlayerState::NONE;
};
