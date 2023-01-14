// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCrashAttackNotify.h"

UPlayerCrashAttackNotify::UPlayerCrashAttackNotify()
{
	InitNotify(FName(TEXT("PlayerCrashAttack")));
}

void UPlayerCrashAttackNotify::PostLoad()
{
	Super::PostLoad();

	
}

void UPlayerCrashAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	EffectSpawn(_meshComp);

}

void UPlayerCrashAttackNotify::NotifyTick(class USkeletalMeshComponent* _meshComp,
	class UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery4/*Player Attack*/);

	ApplyEffectSpeed(_meshComp, _frameDeltaTime);
}

void UPlayerCrashAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
