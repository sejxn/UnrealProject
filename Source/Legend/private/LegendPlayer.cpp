// Fill out your copyright notice in the Description page of Project Settings.


#include "LegendPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerFSM.h"
#include "GameSettingInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "HpBarWidget.h"
#include "Kismet/GameplayStatics.h"

ALegendPlayer::ALegendPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	topViewCam = CreateDefaultSubobject<UCameraComponent>(TEXT("TopViewCam"));
	playerFSM = CreateDefaultSubobject<UPlayerFSM>(TEXT("PlayerFSM"));

	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeRotation(FRotator(-75.0f, 0.0f, 0.0f));
	springArmComp->TargetArmLength = 1200.0f;
	springArmComp->bUsePawnControlRotation = false;
	springArmComp->bInheritPitch = false;
	springArmComp->bInheritYaw = false;
	springArmComp->bInheritRoll = false;
	springArmComp->bEnableCameraLag = true;
	springArmComp->CameraLagSpeed = 10.0f;
	springArmComp->bDoCollisionTest = false;

	topViewCam->SetupAttachment(springArmComp);
	topViewCam->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f));
	topViewCam->bUsePawnControlRotation = false;

	SetCollision(FName(TEXT("Player")));

	const ConstructorHelpers::FObjectFinder<USkeletalMesh>
		tempMesh(TEXT("SkeletalMesh'/Game/Sword_Animations/Demo/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (tempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempMesh.Object);

		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	swordWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordWeapon"));
	swordWeapon->SetupAttachment(GetMesh(), TEXT("weapon_r"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh>
		tempSwordMesh(TEXT("StaticMesh'/Game/Sword_Animations/Demo/Mannequin/Character/Mesh/Sword.Sword'"));
	if (tempSwordMesh.Succeeded())
	{
		swordWeapon->SetStaticMesh(tempSwordMesh.Object);
		
		swordWeapon->SetRelativeLocationAndRotation(FVector(0.0f), FRotator(0.0f));
		swordWeapon->SetCollisionProfileName(FName("NoCollision"));
	}

	const ConstructorHelpers::FObjectFinder<UAnimBlueprint>
		tempAnim(TEXT("AnimBlueprint'/Game/Character/Player/BPA_LegendPlayer.BPA_LegendPlayer'"));
	if (tempAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(tempAnim.Object->GeneratedClass);
	}
}

void ALegendPlayer::BeginPlay()
{
	Super::BeginPlay();

	InitCharacter(FName(TEXT("Player")));
}

void ALegendPlayer::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

void ALegendPlayer::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

	onInputBindingDelegate.Broadcast(_playerInputComponent);
}

float ALegendPlayer::TakeDamage(float _damageAmount, FDamageEvent const& _damageEvent, AController* _eventInstigator, AActor* _damageCauser)
{
	float damage = Super::TakeDamage(_damageAmount, _damageEvent, _eventInstigator, _damageCauser);

	FVector enemyLocation = _damageCauser->GetActorLocation();
	FVector myLocation = GetActorLocation();
	FVector dir = enemyLocation - myLocation;
	FVector forwardVec = GetActorForwardVector();

	// 앞에있는지 뒤에있는지
	float dotProduct = FVector::DotProduct(dir, forwardVec);

	// 적용시킬 데미지
	float applyDamage = ApplyDamage(damage);
	
	EPlayerState playerCurrentState = playerFSM->GetCurrentState();

	if (EPlayerState::BLOCK == playerCurrentState && dotProduct >= 0.0f)
		playerFSM->ChangeState(EPlayerState::PARRY);
	else
	{
		hp -= applyDamage;
		if (hp <= 0.0f)
		{
			playerFSM->ChangeState(EPlayerState::DEATH);
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("LegendMap"));
		}
		else
		{
			playerFSM->ChangeState(EPlayerState::GET_HIT);
		}
	}
	return damage;
}

void ALegendPlayer::InitCharacter(FName _characterName)
{
	Super::InitCharacter(_characterName);

	UGameInstance* gameInstance = GetGameInstance();
	UGameSettingInstance* gameSettingInstance = Cast<UGameSettingInstance>(gameInstance);
	int32 currentLevel = gameSettingInstance->currentLevel;

	hp += currentLevel * increaseHp;
	attack += currentLevel * increaseAttack;
	defense += currentLevel * increaseDefense;
	speed += currentLevel * increaseSpeed;
	moveSpeed += currentLevel * increaseMoveSpeed;

	GetCharacterMovement()->MaxWalkSpeed = moveSpeed;

	if (hpBarComponent)
	{
		UUserWidget* userWidget = hpBarComponent->GetWidget();
		UHpBarWidget* hpBarWidget = Cast<UHpBarWidget>(userWidget);
		if (hpBarWidget)
		{
			hpBarWidget->maxHp = hpBarWidget->currentHp = hp;
		}
	}
}
