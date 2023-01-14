// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LegendPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API ALegendPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALegendPlayerController();

	virtual void BeginPlay() override;

	virtual void PlayerTick(float _deltaTime) override;

	virtual void SetupInputComponent() override;

};
