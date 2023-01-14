// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "DataStructures.h"
#include "BaseAttackNotify.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class LEGEND_API UBaseAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UBaseAttackNotify();

	virtual void PostLoad() override;

	virtual void NotifyBegin(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation,
		float _totalDuration) override;

	virtual void NotifyTick(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation,
		float _frameDeltaTime) override;

	virtual void NotifyEnd(USkeletalMeshComponent* _meshComp, UAnimSequenceBase* _animation) override;

public:
	void InitNotify(FName _attackName);

	void SphereTraceTheRange(USkeletalMeshComponent* _meshComp, ETraceTypeQuery _traceTypeQuery);

	void EffectSpawn(USkeletalMeshComponent* _meshComp);

	void ApplyEffectSpeed(USkeletalMeshComponent* _meshComp, float _frameDeltaTime);

public:
	UNiagaraComponent* GetNiagaraComponent() { return niagaraComponent; }
	void SetNiagaraComponent(UNiagaraComponent* _currentNiagaraComponent) { niagaraComponent = _currentNiagaraComponent; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	UDataTable* attackInfoTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara)
	TMap<float, UNiagaraSystem*> niagaraSystems;

private:
	TArray<AActor*> toIgnore;

	float attackDamage;

	float attackRange;

	UPROPERTY(VisibleAnywhere, Category = Niagara)
	UNiagaraComponent* niagaraComponent;

	FVector niagaraLocation;

	FRotator niagaraRotation;

	FName traceStartName;

	FName traceEndName;
};
