// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAttackTask.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseCharacter.h"
#include "BaseAIAnim.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

UAIAttackTask::UAIAttackTask()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UAIAttackTask::ExecuteTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory)
{
	Super::ExecuteTask(_ownerComp, _nodeMemory);

	ABaseCharacter* myActor = Cast<ABaseCharacter>(_ownerComp.GetAIOwner()->GetPawn());
	if (!myActor)
		return EBTNodeResult::Type::Failed;
	int32 maxInt = myActor->attackName.Num() - 1;
	int32 nameIndex = UKismetMathLibrary::RandomIntegerInRange(0, maxInt);

	myActor->readyToAttack = false;

	UBaseAIAnim* myAnim = Cast<UBaseAIAnim>(myActor->GetMesh()->GetAnimInstance());
	myActor->PlayAnimMontage(myAnim->attackMontage, myActor->speed, myActor->attackName[nameIndex]);

	return EBTNodeResult::Type::InProgress;
}

void UAIAttackTask::TickTask(UBehaviorTreeComponent& _ownerComp, uint8* _nodeMemory, float _deltaSeconds)
{
	ABaseCharacter* myActor = Cast<ABaseCharacter>(_ownerComp.GetAIOwner()->GetPawn());
	if (!myActor)
		FinishLatentTask(_ownerComp, EBTNodeResult::Type::Failed);

	if (myActor->readyToAttack)
		FinishLatentTask(_ownerComp, EBTNodeResult::Type::Succeeded);
}
