// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "HpBarWidget.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const ConstructorHelpers::FObjectFinder<UDataTable>
		tempTable(TEXT("DataTable'/Game/Data/DT_CharacterBaseAbility.DT_CharacterBaseAbility'"));
	if (tempTable.Succeeded())
	{
		characterDataTable = tempTable.Object;
	}

	hpBarComponent = CreateDefaultSubobject<UWidgetComponent>("Widget");
	hpBarComponent->SetupAttachment(RootComponent);
	hpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	hpBarComponent->SetRelativeLocation(FVector(0, 0, 100));

	static ConstructorHelpers::FClassFinder<UUserWidget>
		hpWidget(TEXT("WidgetBlueprint'/Game/ETC/BP_HpBarWidget.BP_HpBarWidget_C'"));
	if (hpWidget.Succeeded())
	{
		hpBarComponent->SetWidgetClass(hpWidget.Class);
		hpBarComponent->SetDrawSize(FVector2D(150, 50));
	}
	//hpBarComponent->SetWidget(hpWidget.Object);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ABaseCharacter::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (hpBarComponent)
	{
		UUserWidget* userWidget = hpBarComponent->GetWidget();
		UHpBarWidget* hpBarWidget = Cast<UHpBarWidget>(userWidget);
		if (hpBarWidget)
		{
			hpBarWidget->currentHp = hp;
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}

float ABaseCharacter::TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent, AController* _eventInstigator, AActor* _damageCauser)
{
	float damage = Super::TakeDamage(_damageAmount, _damageEvent, _eventInstigator, _damageCauser);

	return damage;
}

void ABaseCharacter::InitCharacter(FName _characterName)
{
	FCharacterBaseAbility* tableRow = characterDataTable->FindRow<FCharacterBaseAbility>
		(_characterName, FString(""));

	if (tableRow)
	{
		characterName = _characterName;
		hp = tableRow->hp;
		attack = tableRow->attack;
		defense = tableRow->defense;
		speed = tableRow->speed;
		moveSpeed = tableRow->moveSpeed;
		attackDist = tableRow->attackDist;
	}

	if (hpBarComponent)
	{
		UUserWidget* userWidget = hpBarComponent->GetWidget();
		UHpBarWidget* hpBarWidget = Cast<UHpBarWidget>(userWidget);
		if (hpBarWidget)
		{
			hpBarWidget->maxHp = hpBarWidget->currentHp = hp;
		}
	}
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 420.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;
}

float ABaseCharacter::ApplyDamage(float _attackDamage)
{
	float applyDamage = _attackDamage - (_attackDamage * defense / 100);

	return applyDamage;
}

void ABaseCharacter::SetCollision(FName _collisionName)
{
	Cast<UCapsuleComponent>(GetRootComponent())->SetCollisionProfileName(_collisionName);
	GetMesh()->SetCollisionProfileName(_collisionName);
}

