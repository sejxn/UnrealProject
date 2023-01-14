// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseState.h"

void UBaseState::RegisterFlag(uint32 _stateFlag)
{
	canChangeStateFlag = _stateFlag;
}

bool UBaseState::CanChangeState(uint32 _state)
{
	return (canChangeStateFlag >> _state) & 1;
}
