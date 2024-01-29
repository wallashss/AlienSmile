// Fill out your copyright notice in the Description page of Project Settings.


#include "FunnySpawner.h"

#include "Engine/Blueprint.h"
#include "AlienSmile.h"


// Sets default values
AFunnySpawner::AFunnySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// REGISTER_FUNNY_OBJ(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Chicken.BP_Chicken'"))
	// auto a = TEXT("");

	// FunnyObjectsArr.Add( TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Chicken.BP_Chicken'"));

	// RegisterFunnyObj(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Chicken.BP_Chicken'"));
	// for (auto i : FunnyObjectsArr)
	// {
		
	// }

	
	// auto a = FindObject<UObject>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Monster.BP_Monster'"));

}


void AFunnySpawner::SpawnRandom()
{
	OnSpawn();
	// UE_LOG(LogAlienSmile, Warning, TEXT("Spawn???"));
	// if(!FunnyObjectsBPs.IsEmpty())
	// {
	// 	LastLoc = GetActorLocation();
	// 	LastRot = GetActorRotation();
	// 	GetWorld()->SpawnActor(FunnyObjectsBPs[0]->GeneratedClass, &LastLoc, &LastRot);
	// }
	// else
	// {
	// 	UE_LOG(LogAlienSmile, Warning, TEXT("Empty spawn???"));
	// }


}

void AFunnySpawner::StopSpawn()
{
	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

// Called when the game starts or when spawned
void AFunnySpawner::BeginPlay()
{
	Super::BeginPlay();

	// FunnyObjectsArr = {
	// 	TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Chicken.BP_Chicken'")
	// };


	// for (auto i : FunnyObjectsArr)
	// {
	// 	auto Obj = FindObject<UObject>(nullptr, i);

	// 	if (Obj)
	// 	{

	// 		UE_LOG(LogAlienSmile, Warning, TEXT("Loaded"), i);
	// 		UBlueprint* GeneratedBP = Cast<UBlueprint>(Obj);
	// 		FunnyObjectsBPs.Add(GeneratedBP);
	// 	}
	// 	else
	// 	{
	// 		UE_LOG(LogAlienSmile, Warning, TEXT("Failed load"), i);
	// 	}

	// }

	GetWorldTimerManager().ClearTimer(SpawnTimer);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AFunnySpawner::SpawnRandom, 3.0f, true);
}

// Called every frame
void AFunnySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

