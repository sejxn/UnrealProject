// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttackNotify.h"
#include "BaseCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UPlayerAttackNotify::UPlayerAttackNotify()
{
	InitNotify(FName(TEXT("PlayerAttack")));

}

void UPlayerAttackNotify::PostLoad()
{
	Super::PostLoad();

	

}

void UPlayerAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	AttackEffectSpawn(_meshComp);

}

void UPlayerAttackNotify::NotifyTick(class USkeletalMeshComponent* _meshComp,
	class UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	SphereTraceTheRange(_meshComp, ETraceTypeQuery::TraceTypeQuery4/*Player Attack*/);

	ApplyEffectSpeed(_meshComp, _frameDeltaTime);
}

void UPlayerAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

}

void UPlayerAttackNotify::AttackEffectSpawn(USkeletalMeshComponent* _meshComp)
{
	ABaseCharacter* baseCharacter = Cast<ABaseCharacter>(_meshComp->GetOwner());
	auto it = niagaraSystems.CreateConstIterator();
	float attack = 50.0f;
	if (baseCharacter)
		attack = baseCharacter->attack;
	UNiagaraSystem* niagaraSystem = it->Value;

	// 공격력에 맞는 이펙트 찾음
	for (; it; ++it)
	{
		if (attack < it->Key)
			break;
		niagaraSystem = it->Value;
	}

	UNiagaraComponent* currentNiagaraComponent = GetNiagaraComponent();
	currentNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, _meshComp,
		NAME_None, attackLocation, attackRotation, EAttachLocation::Type::KeepRelativeOffset, true);
	FDetachmentTransformRules transformRules(EDetachmentRule::KeepWorld, true);
	currentNiagaraComponent->DetachFromComponent(transformRules);
	SetNiagaraComponent(currentNiagaraComponent);
}
