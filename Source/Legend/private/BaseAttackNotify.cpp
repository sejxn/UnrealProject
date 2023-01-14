// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttackNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

UBaseAttackNotify::UBaseAttackNotify()
{
	const ConstructorHelpers::FObjectFinder<UDataTable>
		tempTable(TEXT("DataTable'/Game/Data/DT_AttackInformation.DT_AttackInformation'"));
	if (tempTable.Succeeded())
	{
		attackInfoTable = tempTable.Object;
	}
}

void UBaseAttackNotify::PostLoad()
{
	Super::PostLoad();

}

void UBaseAttackNotify::NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _totalDuration)
{
	Super::NotifyBegin(_meshComp, _animation, _totalDuration);

	
}

void UBaseAttackNotify::NotifyTick(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation, float _frameDeltaTime)
{
	Super::NotifyTick(_meshComp, _animation, _frameDeltaTime);
	
}

void UBaseAttackNotify::NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation)
{
	Super::NotifyEnd(_meshComp, _animation);

	toIgnore.Empty();
}

void UBaseAttackNotify::InitNotify(FName _attackName)
{
	FAttackInfo* tableRow = attackInfoTable->FindRow<FAttackInfo>
		(_attackName, FString(""));

	if (tableRow)
	{
		attackDamage = tableRow->attackDamage;
		attackRange = tableRow->attackRange;
		for (auto it = tableRow->niagaraSystems.CreateConstIterator(); it; ++it)
		{
			niagaraSystems.Add(it->Key, it->Value);
		}
		niagaraLocation = tableRow->niagaraLocation;
		niagaraRotation = tableRow->niagaraRotation;
		traceStartName = tableRow->traceStartName;
		traceEndName = tableRow->traceEndName;
	}
}

void UBaseAttackNotify::SphereTraceTheRange(USkeletalMeshComponent* _meshComp, ETraceTypeQuery _traceTypeQuery)
{
	FHitResult HitResult;
	FCollisionQueryParams Params;
	FVector startLocation;
	FVector endLocation;

	if (_meshComp->GetChildComponent(0))
	{
		startLocation = _meshComp->GetChildComponent(0)->GetSocketLocation(traceStartName);
		endLocation = _meshComp->GetChildComponent(0)->GetSocketLocation(traceEndName);
	}
	else
	{
		startLocation = _meshComp->GetSocketLocation(traceStartName);
		endLocation = _meshComp->GetSocketLocation(traceEndName);
	}

	bool isHit = UKismetSystemLibrary::SphereTraceSingle(_meshComp->GetOwner()->GetWorld(),
		startLocation,
		endLocation,
		attackRange,
		_traceTypeQuery, //
		false,
		toIgnore,
		EDrawDebugTrace::None,//ForDuration,
		HitResult,
		true
	);

	if (isHit)
	{
		AActor* damagedActor = HitResult.GetActor();
		ABaseCharacter* causerCharacter = Cast<ABaseCharacter>(_meshComp->GetOwner());
		if (causerCharacter)
		{
			float characterDamage = causerCharacter->attack;
			AController* hitController = causerCharacter->GetController();
			TSubclassOf<UDamageType> damageType = UDamageType::StaticClass();
			UGameplayStatics::ApplyDamage(damagedActor, characterDamage * attackDamage, hitController, _meshComp->GetOwner(), damageType);
		}

		toIgnore.Add(damagedActor);
	}
	
}

void UBaseAttackNotify::EffectSpawn(USkeletalMeshComponent* _meshComp)
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
	
	niagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(niagaraSystem, _meshComp,
		NAME_None, niagaraLocation, niagaraRotation, EAttachLocation::Type::KeepRelativeOffset, true);
	FDetachmentTransformRules transformRules(EDetachmentRule::KeepWorld, true);
	niagaraComponent->DetachFromComponent(transformRules);
}

void UBaseAttackNotify::ApplyEffectSpeed(USkeletalMeshComponent* _meshComp, float _frameDeltaTime)
{
	if (niagaraComponent)
	{
		ABaseCharacter* baseCharacter = Cast<ABaseCharacter>(_meshComp->GetOwner());
		float speed = 1.0f;
		if (baseCharacter)
			speed = baseCharacter->speed;
		niagaraComponent->AdvanceSimulation(1, _frameDeltaTime * speed);
	}
}

