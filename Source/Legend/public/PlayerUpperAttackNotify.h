// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAttackNotify.h"
#include "PlayerUpperAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UPlayerUpperAttackNotify : public UBaseAttackNotify
{
	GENERATED_BODY()
	
public:
	UPlayerUpperAttackNotify();

public:
	virtual void PostLoad() override;

	virtual void NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation,
		float _totalDuration) override;

	virtual void NotifyTick(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation,
		float _frameDeltaTime) override;

	virtual void NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation) override;
};
