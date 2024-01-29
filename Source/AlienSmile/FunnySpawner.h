// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunnySpawner.generated.h"

class UBlueprint;
UCLASS()
class ALIENSMILE_API AFunnySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFunnySpawner();

	UFUNCTION()
	void SpawnRandom();

	UFUNCTION(BlueprintCallable)
	void StopSpawn();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	TArray<UBlueprint*> FunnyObjectsBPs;

	FVector LastLoc;
	FRotator LastRot;

	FTimerHandle SpawnTimer;

};
