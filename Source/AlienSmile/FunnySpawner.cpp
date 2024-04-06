// Fill out your copyright notice in the Description page of Project Settings.


#include "FunnySpawner.h"

#include "Engine/Blueprint.h"
#include "AlienSmile.h"
#include <Kismet/KismetMathLibrary.h>

static const float SPAWN_TIMER = 2.5f;
// Sets default values
AFunnySpawner::AFunnySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	IsNewSpawner = false;

	ItemIdx = 0;


}

void AFunnySpawner::SpawnRandom()
{
	OnSpawn();

	if(Objects.Num())
	{
		FActorSpawnParameters SpawnInfo;
		
		// auto idx = FMath::RandRange(0, Objects.Num() - 1);
		LastLoc = GetActorLocation();
		LastRot = GetActorRotation();

		if(ItemIdx < Objects.Num())
		{
			GetWorld()->SpawnActor(Objects[ItemIdx], &LastLoc, &LastRot);
		}

		ItemIdx++;

		// Random Round-robin
		if(ItemIdx >= Objects.Num())
		{
			ItemIdx = 0;
			Shuffle();
		}
	}
}

void AFunnySpawner::StopSpawn()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void AFunnySpawner::StartSpawn()
{
	Shuffle();
	GetWorldTimerManager().ClearTimer(SpawnTimer);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AFunnySpawner::SpawnRandom, SPAWN_TIMER, true);
}

// Called when the game starts or when spawned
void AFunnySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFunnySpawner::Shuffle()
{
	if (Objects.Num() > 0)
     {
          int32 LastIndex = Objects.Num() - 1;
          for (int32 i = 0; i <= LastIndex; ++i)
          {
               int32 Index = FMath::RandRange(i, Objects.Num() -1);
               if (i != Index)
               {
                    Objects.Swap(i, Index);
               }
          }
     }
}

