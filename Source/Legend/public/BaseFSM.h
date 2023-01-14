// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseState.h"
#include "BaseFSM.generated.h"

class ABaseCharacter;
class AController;
class UAnimInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), abstract )
class LEGEND_API UBaseFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;
	virtual void InitializeComponent() override {}

public:
	virtual ABaseCharacter* GetOwnerCharacter();
	virtual AController* GetController();
	virtual UAnimInstance* GetAnim();
	
	UBaseState* GetBaseState() { return currentBaseState; }
	void SetBaseState(UBaseState* _state) { currentBaseState = _state; }

	void PushState(UBaseState* _state) { states.Add(_state); }

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = States)
	TArray<UBaseState*> states;

private:
	UBaseState* currentBaseState = nullptr;
};
