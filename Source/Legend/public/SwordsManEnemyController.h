// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "SwordsManEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API ASwordsManEnemyController : public AEnemyController
{
	GENERATED_BODY()
	
public:
	ASwordsManEnemyController();

	virtual void BeginPlay() override;
};
