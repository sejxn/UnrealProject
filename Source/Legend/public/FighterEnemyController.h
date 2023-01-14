// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyController.h"
#include "FighterEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API AFighterEnemyController : public AEnemyController
{
	GENERATED_BODY()
	
public:
	AFighterEnemyController();

	virtual void BeginPlay() override;

};
