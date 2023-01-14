// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDeathState.h"
#include "Enemy.h"
#include "EnemyFSM.h"
#include "EnemyAnim.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyGenerator.h"
#include "GameSettingInstance.h"

UEnemyDeathState::UEnemyDeathState()
{
	RegisterFlag(1 << static_cast<uint32>(EEnemyState::IDLE));
}

void UEnemyDeathState::BeginState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AEnemy* enemy = Cast<AEnemy>(enemyFSM->GetOwner());
	UEnemyAnim* enemyAnim = Cast<UEnemyAnim>(enemyFSM->GetAnim());
	float montageTime = enemy->PlayAnimMontage(enemyAnim->getHitMontage, 1.0f, "EnemyDeath");

	enemy->SetCollision(FName(TEXT("Death")));

	enemyFSM->GetOwner()->GetWorld()->GetTimerManager().SetTimer(returnTimerHandle, this, &UEnemyDeathState::ReturnObject, montageTime - 1.0f);

	UGameInstance* gameInstance = enemyFSM->GetOwner()->GetGameInstance();
	UGameSettingInstance* gameSettingInstance = Cast<UGameSettingInstance>(gameInstance);
	gameSettingInstance->currentEnemyNum += 1;
}

void UEnemyDeathState::UpdateState(float _deltaTime)
{

}

void UEnemyDeathState::EndState()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AEnemy* enemy = Cast<AEnemy>(enemyFSM->GetOwner());

	enemy->StopAnimMontage();
}

void UEnemyDeathState::ReturnObject()
{
	UEnemyFSM* enemyFSM = GetEnemyFSM();
	AActor* generatorActor = UGameplayStatics::GetActorOfClass(enemyFSM->GetOwner()->GetWorld(), AEnemyGenerator::StaticClass());
	AEnemyGenerator* enemyGenerator = Cast<AEnemyGenerator>(generatorActor);
	enemyGenerator->ReturnPoolObject(enemyFSM->GetOwnerCharacter());
}
