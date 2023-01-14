// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseState.h"
#include "EnemyAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEnemyAnim();

	virtual void NativeUpdateAnimation(float _deltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim)
	float speed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyState)
 	EEnemyState enemyState = EEnemyState::IDLE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyAnim)
	UAnimMontage* attackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyAnim)
	UAnimMontage* getHitMontage;
};
