// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAIAnim.h"
#include "SwordsManEnemyAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class LEGEND_API USwordsManEnemyAnim : public UBaseAIAnim
{
	GENERATED_BODY()
	
public:
	USwordsManEnemyAnim();

	virtual void NativeUpdateAnimation(float _deltaSeconds) override;
};
