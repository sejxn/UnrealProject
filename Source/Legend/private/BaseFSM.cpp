// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseFSM.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UBaseFSM::UBaseFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	// ...
}


// Called when the game starts
void UBaseFSM::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBaseFSM::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);

	// ...
}

ABaseCharacter* UBaseFSM::GetOwnerCharacter()
{
	ABaseCharacter* ownerCharacter = Cast<ABaseCharacter>(GetOwner());
	return ownerCharacter;
}

AController* UBaseFSM::GetController()
{
	AController* ownerController = GetOwnerCharacter()->GetController();
	
	return ownerController;
}

UAnimInstance* UBaseFSM::GetAnim()
{
	UAnimInstance* ownerAnim = GetOwnerCharacter()->GetMesh()->GetAnimInstance();
	
	return ownerAnim;
}

