// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "AlienSmile.h"
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>

#include <GameFramework/CharacterMovementComponent.h>
#include "FunnyObject.h"
#include <Engine/TriggerBase.h>

#include <Kismet/KismetMathLibrary.h>

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// MouthCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Mouth"));

	MonsterSpeed = 100.0f;

	InitialHP = HP = 5;

	Dead = false;

	SmilingCooldown = 5.0f;

	IsSmiling = false;

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = MonsterSpeed;

	MonsterDir = GetActorForwardVector();

	MonsterRot = GetActorRotation();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnMonsterOverlap);
	OnActorHit.AddDynamic(this, &AMonster::OnMonsterHit);
	
	// IsMoving = true;
	
}

void AMonster::OnMonsterOverlap(UPrimitiveComponent* OverlappedComponent, 
										  AActor* OtherActor, 
										  UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult)
{

	// UE_LOG(LogAlienSmile, Warning, TEXT("MOnster OVERLAP: %s"), *OtherActor->GetActorLabel());

}

void AMonster::OnMonsterHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& hit)
{
	auto FunnyObj = OtherActor->GetComponentByClass<UFunnyObject>();

	if(!FunnyObj)
	{
		return;
	}

	
	if (FunnyObj->Activated)
	{
		return;
	}

	if (FunnyObj->FunnyIndex != FunnyIdx)
	{
		return;
	}

	FunnyObj->Activated = true;
	Smile();


}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMoving)
	{
		SetActorRotation(MonsterRot);
		AddMovementInput(MonsterDir);
	}

}

void AMonster::StopMove()
{
	IsMoving = false;
}

void AMonster::SetDamage()
{
	// WPRINT(TEXT("Damage %d"), HP);

	if (!IsSmiling)
	{
		return;
	}
	else
	{
		UE_LOG(LogAlienSmile, Warning, TEXT("Not smiling"));
	}

	
	if(!Dead)
	{
		HP--;
		UE_LOG(LogAlienSmile, Warning, TEXT("DAMAGE %d"), HP);

		OnMonsterDamage();
		CheckDead();
	}
	else
	{
		UE_LOG(LogAlienSmile, Warning, TEXT("Monster is DEAD"));
	}
}

void AMonster::SetWinner()
{
	StopMove();
	OnMonsterWinner();
}

bool AMonster::CheckDead()
{
	if(HP <= 0)
	{
		StopMove();
		OnMonsterDead();
		Dead = true;

		OnMonsterDefeated.Broadcast();
		return true;
	}
	return false;
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::Smile()
{
	IsMoving = false;
	OnMonsterSmiling();

	GetWorldTimerManager().SetTimer(SmilingCooldownTimer, this, &AMonster::StopSmiling, SmilingCooldown, false);

	IsSmiling = true;
}

void AMonster::StopSmiling()
{
	IsMoving = true;
	IsSmiling = false;

	SetActorRotation(MonsterRot);
	OnMonsterStopSmiling();
}


void AMonster::ResetMonster()
{
	HP = InitialHP;
	Dead = false;
	IsMoving = true;

	IsMoving = true;
	IsSmiling = false;

	SetActorRotation(MonsterRot);
	OnMonsterStopSmiling();
}
