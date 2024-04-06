// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AlienGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreUp);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);


/**
 * 
 */
UCLASS()
class ALIENSMILE_API AAlienGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AAlienGameState();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnMonster();

	UFUNCTION(BlueprintCallable)
	void SetupGame(AActor * SpawnLoc, AActor * GameOver);

	UFUNCTION(BlueprintCallable)
	void InitGame();

	UFUNCTION(BlueprintCallable)
	void ResetGame();

	UFUNCTION(BlueprintCallable)
	void OnMonsterDefeated();

	UFUNCTION(BlueprintCallable)
	void RequestNewMonster();

	UFUNCTION(BlueprintCallable)
	FTransform GetSpawnTransform();

	UFUNCTION(BlueprintCallable)
	void ResetPlayer();

	UFUNCTION(BlueprintCallable)
	void SetGameOver();

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void ResumeGame();

	UFUNCTION()
	void OnDefeatTriggerOverlap(UPrimitiveComponent* OverlappedComponent, 
										  AActor* OtherActor, 
										  UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult);
public:

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnDir;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* GameOverMesh;

	UObject * MonsterObject;

	UObject * ProjectileObject;

	UClass * ProjectileClass;

	class AScorePanel * ScorePanel;

	FTransform SpawnTransform;

	FTimerHandle SpawnTimer;

	FTimerHandle ResetPlayerTimer;

	FTimerHandle ResetGameTimer;

	class AMonster * CurrentMonster;

	UPROPERTY( BlueprintAssignable, Category= "Events")
	FOnGameOver OnGameOver;

	UPROPERTY( BlueprintAssignable, Category= "Events")
	FOnScoreUp OnScoreUp;

	UPROPERTY( BlueprintAssignable, Category= "Events")
	FOnGameStart OnGameStart;

	int Score;

	int32 FunnyIndicesCount;
	
};
