// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordsManEnemy.h"
#include "SwordsManEnemyController.h"

ASwordsManEnemy::ASwordsManEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	SetCollision(FName(TEXT("Enemy")));

	AIControllerClass = ASwordsManEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		tempMesh(TEXT("SkeletalMesh'/Game/Sword_Animations/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	swordWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordWeapon"));
	swordWeapon->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh>
		tempSwordMesh(TEXT("StaticMesh'/Game/Sword_Animations/Demo/Mannequin/Character/Mesh/Sword.Sword'"));
	if (tempSwordMesh.Succeeded())
	{
		swordWeapon->SetStaticMesh(tempSwordMesh.Object);

		swordWeapon->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f));
		swordWeapon->SetCollisionProfileName(FName("NoCollision"));
	}

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		tempAnim(TEXT("AnimBlueprint'/Game/Character/Enemy/AISwordsMan/BPA_SwordsManEnemy.BPA_SwordsManEnemy'"));
	if (tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Object->GeneratedClass);
	}
}

void ASwordsManEnemy::BeginPlay()
{
	Super::BeginPlay();

}

void ASwordsManEnemy::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);


}

float ASwordsManEnemy::TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent, AController* _eventInstigator, AActor* _damageCauser)
{
	float damage = Super::TakeDamage(_damageAmount, _damageEvent, _eventInstigator, _damageCauser);

	float applyDamage = ApplyDamage(damage);

	hp -= applyDamage;

	return damage;
}

void ASwordsManEnemy::RunAI()
{
	AEnemyController* enemyController = Cast<AEnemyController>(GetController());
	enemyController->RunAI();
	SetActorHiddenInGame(false);
	SetCollision(FName(TEXT("Enemy")));
}

void ASwordsManEnemy::StopAI()
{
	AEnemyController* enemyController = Cast<AEnemyController>(GetController());
	enemyController->StopAI();
	SetActorHiddenInGame(true);
	SetCollision(FName(TEXT("Death")));
}
