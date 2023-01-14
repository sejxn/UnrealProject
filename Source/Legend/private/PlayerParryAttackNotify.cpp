// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerParryAttackNotify.h"

UPlayerParryAttackNotify::UPlayerParryAttackNotify()
{
	InitNotify(FName(TEXT("PlayerParryAttack")));

}

void UPlayerParryAttackNotify::PostLoad()
{
	Super::PostLoad();

	
}

void UPlayerParryAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	EffectSpawn(_meshComp);

}

void UPlayerParryAttackNotify::NotifyTick(class USkeletalMeshComponent* _meshComp,
	class UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery4/*Player Attack*/);

	ApplyEffectSpeed(_meshComp, _frameDeltaTime);
}

void UPlayerParryAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
