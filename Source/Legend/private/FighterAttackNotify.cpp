// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterAttackNotify.h"

UFighterAttackNotify::UFighterAttackNotify()
{
	InitNotify(FName(TEXT("FighterAttack")));

}

void UFighterAttackNotify::PostLoad()
{
	Super::PostLoad();

}

void UFighterAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	
}

void UFighterAttackNotify::NotifyTick(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery5/*Enemy Attack*/);

}

void UFighterAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}
