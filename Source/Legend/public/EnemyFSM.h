// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseFSM.h"
#include "EnemyFSM.generated.h"

class ALegendPlayer;

/**
 * 
 */
UCLASS()
class LEGEND_API UEnemyFSM : public UBaseFSM
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
	bool ChangeState(EEnemyState _enemyState);

	ALegendPlayer* GetTarget() { return target; }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = States)
	EEnemyState enemyState = EEnemyState::NONE;

private:
	ALegendPlayer* target;
};
