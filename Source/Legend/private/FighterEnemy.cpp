// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterEnemy.h"
#include "FighterEnemyController.h"

AFighterEnemy::AFighterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCollision(FName(TEXT("Enemy")));

	AIControllerClass = AFighterEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		tempMesh(TEXT("SkeletalMesh'/Game/FighterAnimationPack/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		tempAnim(TEXT("AnimBlueprint'/Game/Character/Enemy/AIFighter/BPA_FighterEnemy.BPA_FighterEnemy'"));
	if (tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Object->GeneratedClass);
	}
}

void AFighterEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFighterEnemy::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

float AFighterEnemy::TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent, AController* _eventInstigator, AActor* _damageCauser)
{
	float damage = Super::TakeDamage(_damageAmount, _damageEvent, _eventInstigator, _damageCauser);

	float applyDamage = ApplyDamage(damage);

	hp -= applyDamage;

	return damage;
}

void AFighterEnemy::RunAI()
{
	AEnemyController* enemyController = Cast<AEnemyController>(GetController());
	enemyController->RunAI();
	SetActorHiddenInGame(false);
	SetCollision(FName(TEXT("Enemy")));
}

void AFighterEnemy::StopAI()
{
	AEnemyController* enemyController = Cast<AEnemyController>(GetController());
	enemyController->StopAI();
	SetActorHiddenInGame(true);
	SetCollision(FName(TEXT("Death")));
}
