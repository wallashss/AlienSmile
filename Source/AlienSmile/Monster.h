// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterDefeated);


UCLASS()
class ALIENSMILE_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	UPROPERTY(EditAnywhere, Category = "Alien")
	bool IsMoving;

	UPROPERTY(EditAnywhere, Category = "Alien")
	float MonsterSpeed;

	UPROPERTY(EditAnywhere, Category = "Alien")
	class UCapsuleComponent * MouthCapsule;

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void StopMove();

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void SetDamage();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMouthCollision();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMonsterDead();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMonsterWinner();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMonsterSmiling();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMonsterStopSmiling();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnMonsterDamage();

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void SetWinner();

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void Smile();

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void StopSmiling();

	UFUNCTION(Category = "Alien")
	void OnMonsterOverlap(class UPrimitiveComponent* OverlappedComponent, 
										  class AActor* OtherActor, 
										  class UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult);

	UFUNCTION(Category = "Alien")
	void OnMonsterHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& hit);

	UFUNCTION(Category = "Alien")
	void OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void IncreaseSpeed(float DeltaSpeed);

	UFUNCTION(BlueprintCallable, Category = "Alien")
	void SetTarget(FVector Target);

	bool CheckDead();

	void ResetMonster();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, Category = "Alien")
	int HP;

	UPROPERTY(EditAnywhere, Category = "Alien")
	int InitialHP;

	// UPROPERTY(VisibleAnywhere, Category = "Alien")
	bool Dead;

	UPROPERTY(EditAnywhere, Category = "Alien")
	bool IsSmiling;

	UPROPERTY(EditAnywhere, Category = "Alien")
	int32 FunnyIdx;

	UPROPERTY(EditAnywhere, Category = "Alien")
	float SmilingCooldown;
	
	FTimerHandle SmilingCooldownTimer;

	FVector MonsterDir;

	FRotator MonsterRot;

	FVector Target;

	FOnMonsterDefeated OnMonsterDefeated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alien")
	class USkeletalMeshComponent * Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alien")
	class UCapsuleComponent * Capsule;

	float FloorHeight;


};
