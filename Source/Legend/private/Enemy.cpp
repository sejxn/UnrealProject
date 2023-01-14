// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "EnemyFSM.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	enemyFSM = CreateDefaultSubobject<UEnemyFSM>(TEXT("EnemyFSM"));

	SetCollision(FName(TEXT("Enemy")));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		tempMesh(TEXT("SkeletalMesh'/Game/Sword_Animations/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		tempAnim(TEXT("AnimBlueprint'/Game/Character/Enemy/Zombie/BPA_Enemy.BPA_Enemy'"));
	if (tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Object->GeneratedClass);
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemy::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

float AEnemy::TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent, AController* _eventInstigator, AActor* _damageCauser)
{
	float damage = Super::TakeDamage(_damageAmount, _damageEvent, _eventInstigator, _damageCauser);

	float applyDamage = ApplyDamage(damage);

	hp -= applyDamage;
	if (hp <= 0.0f)
	{
		enemyFSM->ChangeState(EEnemyState::DEATH);
	}
	else
	{
		enemyFSM->ChangeState(EEnemyState::GET_HIT);
	}

	return damage;
}

void AEnemy::RunAI()
{
	enemyFSM->SetComponentTickEnabled(true);
	enemyFSM->ChangeState(EEnemyState::IDLE);
	SetActorHiddenInGame(false);
	SetCollision(FName(TEXT("Enemy")));
}

void AEnemy::StopAI()
{
	enemyFSM->SetComponentTickEnabled(false);
	enemyFSM->ChangeState(EEnemyState::IDLE);
	SetActorHiddenInGame(true);
	SetCollision(FName(TEXT("Death")));
}
