// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "LegendPlayer.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FInputBindingDelegate, UInputComponent*);

class USpringArmComponent;
class UCameraComponent;
class UPlayerFSM;

/**
 * 
 */
UCLASS()
class LEGEND_API ALegendPlayer : public ABaseCharacter
{
	GENERATED_BODY()

public:
	FInputBindingDelegate onInputBindingDelegate;

public:
	ALegendPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float _deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* _playerInputComponent) override;

	virtual float TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent,
		AController* _eventInstigator, AActor* _damageCauser) override;

	virtual void InitCharacter(FName _characterName) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	UStaticMeshComponent* swordWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	USpringArmComponent* springArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	UCameraComponent* topViewCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FSM)
	UPlayerFSM* playerFSM;

private:
	float increaseHp = 10.0f;
	float increaseAttack = 8.0f;
	float increaseDefense = 2.0f;
	float increaseSpeed = 0.05f;
	float increaseMoveSpeed = 10.0f;
};
