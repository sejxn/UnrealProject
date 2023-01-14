// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSlashAttackNotify.h"

UPlayerSlashAttackNotify::UPlayerSlashAttackNotify()
{
	InitNotify(FName(TEXT("PlayerSlashAttack")));
}

void UPlayerSlashAttackNotify::PostLoad()
{
	Super::PostLoad();

	
}

void UPlayerSlashAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	EffectSpawn(_meshComp);

}

void UPlayerSlashAttackNotify::NotifyTick(class USkeletalMeshComponent* _meshComp,
	class UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery4/*Player Attack*/);

	ApplyEffectSpeed(_meshComp, _frameDeltaTime);
}

void UPlayerSlashAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
