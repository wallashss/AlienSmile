// Fill out your copyright notice in the Description page of Project Settings.


#include "FunnySpawner.h"

#include "Engine/Blueprint.h"
#include "AlienSmile.h"
#include <Kismet/KismetMathLibrary.h>


// Sets default values
AFunnySpawner::AFunnySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	IsNewSpawner = false;
}

void AFunnySpawner::SpawnRandom()
{
	OnSpawn();

	if(Objects.Num())
	{
		FActorSpawnParameters SpawnInfo;
		
		auto idx = FMath::RandRange(0, Objects.Num() - 1);
		LastLoc = GetActorLocation();
		LastRot = GetActorRotation();
		GetWorld()->SpawnActor(Objects[idx], &LastLoc, &LastRot);
	}
}

void AFunnySpawner::StopSpawn()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void AFunnySpawner::StartSpawn()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AFunnySpawner::SpawnRandom, 3.0f, true);
}

// Called when the game starts or when spawned
void AFunnySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

