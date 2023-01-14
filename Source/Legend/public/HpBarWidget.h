// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class LEGEND_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category = HP)
	float maxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HP)
	float currentHp;
};
