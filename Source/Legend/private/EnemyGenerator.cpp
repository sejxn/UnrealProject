// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGenerator.h"
#include "Enemy.h"
#include "FighterEnemy.h"
#include "SwordsManEnemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameSettingInstance.h"

// Sets default values
AEnemyGenerator::AEnemyGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	LevelInit();

	CreateEnemy();

	SpawnEnemy();
}

// Called every frame
void AEnemyGenerator::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void AEnemyGenerator::SpawnPoolObject()
{
	if (currentEnemyNum >= maxEnemyNum)
		return;
	int32 maxNum = enemyNames[currentLevel].enemyName.Num() - 1;
	int32 randomNum = UKismetMathLibrary::RandomIntegerInRange(0, maxNum);
	FName enemyName = enemyNames[currentLevel].enemyName[randomNum];
	FVector spawnPoint = GetSpawnPoint();
	if (FighterEnemyName == enemyName)
	{
		if (!fighterEnemyPool.IsEmpty())
		{
			AFighterEnemy* fighterEnemy;
			fighterEnemyPool.Dequeue(fighterEnemy);
			fighterEnemy->InitCharacter(enemyName);
			fighterEnemy->RunAI();
			fighterEnemy->SetActorLocation(spawnPoint);
			++currentEnemyNum;
		}
	}
	else if (SwordsManEnemyName == enemyName)
	{
		if (!swordsManEnemyPool.IsEmpty())
		{
			ASwordsManEnemy* swordsManEnemy;
			swordsManEnemyPool.Dequeue(swordsManEnemy);
			swordsManEnemy->InitCharacter(enemyName);
			swordsManEnemy->RunAI();
			swordsManEnemy->SetActorLocation(spawnPoint);
			++currentEnemyNum;
		}
	}
	else
	{
		if (!enemyPool.IsEmpty())
		{
			AEnemy* enemy;
			enemyPool.Dequeue(enemy);
			enemy->InitCharacter(enemyName);
			enemy->RunAI();
			enemy->SetActorLocation(spawnPoint);
			++currentEnemyNum;
		}
	}
}

void AEnemyGenerator::ReturnPoolObject(ABaseCharacter* _poolEnemy)
{
	if (FighterEnemyName == _poolEnemy->characterName)
	{
		AFighterEnemy* fighterEnemy = Cast<AFighterEnemy>(_poolEnemy);
		fighterEnemy->StopAI();
		fighterEnemyPool.Enqueue(fighterEnemy);
	}
	else if (SwordsManEnemyName == _poolEnemy->characterName)
	{
		ASwordsManEnemy* swordsManEnemy = Cast<ASwordsManEnemy>(_poolEnemy);
		swordsManEnemy->StopAI();
		swordsManEnemyPool.Enqueue(swordsManEnemy);
	}
	else
	{
		AEnemy* enemy = Cast<AEnemy>(_poolEnemy);
		enemy->StopAI();
		enemyPool.Enqueue(enemy);
	}
}

void AEnemyGenerator::LevelInit()
{
	UGameInstance* gameInstance = GetGameInstance();
	UGameSettingInstance* gameSettingInstance = Cast<UGameSettingInstance>(gameInstance);
	currentLevel = gameSettingInstance->currentLevel;
	maxEnemyNum = gameSettingInstance->maxEnemyNum;
}

void AEnemyGenerator::CreateEnemy()
{
	// 스폰 포인트 초기화
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), allActors);
	for (auto spawn : allActors)
	{
		if (spawn->GetName().Contains(TEXT("BP_EnemySpawnPoint")))
		{
			spawnPoints.Add(spawn);
		}
	}

	// 에너미 미리 생성 후 풀링
	for (int32 i = 0; i < enemyNames[currentLevel].enemyName.Num(); ++i)
	{
		if (FighterEnemyName == enemyNames[currentLevel].enemyName[i])
		{
			for (int32 j = 0; j < poolObjectNum; ++j)
			{
				AFighterEnemy* fighterEnemy = GetWorld()->SpawnActor<AFighterEnemy>(fighterEnemyFactory);
				fighterEnemy->StopAI();
				fighterEnemyPool.Enqueue(fighterEnemy);
			}
		}
		else if (SwordsManEnemyName == enemyNames[currentLevel].enemyName[i])
		{
			for (int32 j = 0; j < poolObjectNum; ++j)
			{
				ASwordsManEnemy* swordsManEnemy = GetWorld()->SpawnActor<ASwordsManEnemy>(swordsManEnemyFactory);
				swordsManEnemy->StopAI();
				swordsManEnemyPool.Enqueue(swordsManEnemy);
			}
		}
		else
		{
			for (int32 j = 0; j < poolObjectNum; ++j)
			{
				AEnemy* enemy = GetWorld()->SpawnActor<AEnemy>(enemyFactory);
				enemy->StopAI();
				enemyPool.Enqueue(enemy);
			}
		}
	}
}

void AEnemyGenerator::SpawnEnemy()
{
	SpawnPoolObject();

	GetWorld()->GetTimerManager().SetTimer(spawnTimerHandle, this, &AEnemyGenerator::SpawnEnemy, 2.0f);
}

FVector AEnemyGenerator::GetSpawnPoint()
{
	int32 maxNum = spawnPoints.Num() - 1;
	int32 randomNum = UKismetMathLibrary::RandomIntegerInRange(0, maxNum);
	FVector spawnPoint = spawnPoints[randomNum]->GetActorLocation();
	return spawnPoint;
}

