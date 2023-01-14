// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyGenerator.generated.h"

class AEnemy;
class AFighterEnemy;
class ASwordsManEnemy;
class ABaseCharacter;

USTRUCT()
struct FNestedArray
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TArray<FName> enemyName;
};

UCLASS()
class LEGEND_API AEnemyGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float _deltaTime) override;

public:
	void SpawnPoolObject();

	UFUNCTION(BlueprintCallable)
	void ReturnPoolObject(ABaseCharacter* _poolEnemy);

private:
	void LevelInit();
	void CreateEnemy();
	void SpawnEnemy();
	FVector GetSpawnPoint();

public:
	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TSubclassOf<AEnemy> enemyFactory;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TSubclassOf<AFighterEnemy> fighterEnemyFactory;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TSubclassOf<ASwordsManEnemy> swordsManEnemyFactory;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TArray<FNestedArray> enemyNames;

	UPROPERTY(EditAnywhere, Category = SpawnEnemy)
	TArray<AActor*> spawnPoints;

private:
	TQueue<AEnemy*> enemyPool;
	TQueue<AFighterEnemy*> fighterEnemyPool;
	TQueue<ASwordsManEnemy*> swordsManEnemyPool;

	int32 poolObjectNum = 10;
	uint32 currentLevel = 0;
	uint32 maxEnemyNum = 0;
	uint32 currentEnemyNum = 0;

	FTimerHandle spawnTimerHandle;

	const FName FighterEnemyName = FName(TEXT("FighterEnemy"));
	const FName SwordsManEnemyName = FName(TEXT("SwordsManEnemy"));
};