// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

#include "DataStructures.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterBaseAbility : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float defense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackDist;
};

USTRUCT(BlueprintType)
struct FAttackInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<float, UNiagaraSystem*> niagaraSystems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector niagaraLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator niagaraRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName traceStartName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName traceEndName;
};