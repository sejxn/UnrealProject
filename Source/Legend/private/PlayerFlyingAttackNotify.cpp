// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFlyingAttackNotify.h"

UPlayerFlyingAttackNotify::UPlayerFlyingAttackNotify()
{
	InitNotify(FName(TEXT("PlayerFlyingAttack")));
}

void UPlayerFlyingAttackNotify::PostLoad()
{
	Super::PostLoad();

	
}

void UPlayerFlyingAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	EffectSpawn(_meshComp);

}

void UPlayerFlyingAttackNotify::NotifyTick(class USkeletalMeshComponent* _meshComp,
	class UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery4/*Player Attack*/);

	ApplyEffectSpeed(_meshComp, _frameDeltaTime);
}

void UPlayerFlyingAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
