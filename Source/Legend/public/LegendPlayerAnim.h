// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseState.h"
#include "LegendPlayerAnim.generated.h"

class UAnimMontage;

/**
 * 
 */
UCLASS()
class LEGEND_API ULegendPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	ULegendPlayerAnim();

	virtual void NativeUpdateAnimation(float _deltaSeconds) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float speed = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerAnim)
	UAnimMontage* attackMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerAnim)
	UAnimMontage* getHitMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerAnim)
	UAnimMontage* dashMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = PlayerAnim)
	UAnimMontage* skillMontage;
};
