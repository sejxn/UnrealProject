// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAIAnim.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UBaseAIAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float _deltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = EnemyAnim)
	float speed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyAnim)
	UAnimMontage* attackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyAnim)
	UAnimMontage* deathMontage;
};
