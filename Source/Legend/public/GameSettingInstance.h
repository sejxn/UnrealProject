// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameSettingInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UGameSettingInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	int32 currentLevel = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Level)
	int32 maxEnemyNum = 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Level)
	int32 currentEnemyNum = 0;
};
