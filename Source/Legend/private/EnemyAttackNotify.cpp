// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackNotify.h"

UEnemyAttackNotify::UEnemyAttackNotify()
{
	InitNotify(FName(TEXT("EnemyAttack")));
}

void UEnemyAttackNotify::PostLoad()
{
	Super::PostLoad();

	
}

void UEnemyAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	
}

void UEnemyAttackNotify::NotifyTick(USkeletalMeshComponent* _meshComp,
	UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery5/*Enemy Attack*/);

}

void UEnemyAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
