// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerDeathState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerDeathState : public UPlayerBaseState
{
	GENERATED_BODY()
	
public:
	UPlayerDeathState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;
};
