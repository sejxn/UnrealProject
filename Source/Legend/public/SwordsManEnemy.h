// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "SwordsManEnemy.generated.h"

class AEnemyGenerator;

/**
 * 
 */
UCLASS()
class LEGEND_API ASwordsManEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ASwordsManEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float _deltaTime) override;

	virtual float TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent,
		AController* _eventInstigator, AActor* _damageCauser) override;

	virtual void RunAI() override;
	virtual void StopAI() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	UStaticMeshComponent* swordWeapon;
};
