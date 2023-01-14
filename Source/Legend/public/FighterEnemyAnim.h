// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIAnim.h"
#include "FighterEnemyAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class LEGEND_API UFighterEnemyAnim : public UBaseAIAnim
{
	GENERATED_BODY()
	
public:
	UFighterEnemyAnim();

	virtual void NativeUpdateAnimation(float _deltaSeconds) override;
};
