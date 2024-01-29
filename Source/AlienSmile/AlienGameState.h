// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AlienGameState.generated.h"

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
	void SetupGame(AActor * SpawnLoc, AActor * DefeatTrigger, UClass * ProjectileClass);

	UFUNCTION(BlueprintCallable)
	void RequestNewMonster();

	UFUNCTION(BlueprintCallable)
	FTransform GetSpawnTransform();

	UPROPERTY(VisibleAnywhere)
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	FVector SpawnDir;

	UPROPERTY(VisibleAnywhere)
	FRotator SpawnRotation;

	UObject * MonsterObject;

	UObject * ProjectileObject;

	UClass * ProjectileClass;

	FTransform SpawnTransform;

	FTimerHandle SpawnTimer;

	class AMonster * CurrentMonster;
	
};
