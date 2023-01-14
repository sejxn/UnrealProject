// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DataStructures.h"
#include "BaseCharacter.generated.h"

class UWidgetComponent;

UCLASS()
class LEGEND_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float _deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;

	virtual float TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent,
		AController* _eventInstigator, AActor* _damageCauser) override;

	virtual void RunAI() {};
	virtual void StopAI() {};

public:
	virtual void InitCharacter(FName _characterName);
	
	float ApplyDamage(float _attackDamage);

	UFUNCTION(BlueprintCallable)
	void SetCollision(FName _collisionName);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = DataTable)
	UDataTable* characterDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	FName characterName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float hp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float defense;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float moveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterSetting)
	float attackDist;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HP)
	UWidgetComponent* hpBarComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TArray<FName> attackName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool readyToAttack = true;
};
