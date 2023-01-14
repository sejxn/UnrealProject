// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerBaseState.h"
#include "PlayerGetHitState.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerGetHitState : public UPlayerBaseState
{
	GENERATED_BODY()
	
public:
	UPlayerGetHitState();

public:
	virtual void BeginState() override;
	virtual void UpdateState(float _deltaTime) override;
	virtual void EndState() override;
};
