// Fill out your copyright notice in the Description page of Project Settings.


#include "DefeatTrigger.h"

#include <Components/BoxComponent.h>

#include "AlienSmile.h"
#include "Monster.h"


// Sets default values
ADefeatTrigger::ADefeatTrigger()
{

	BoxColisor = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColisor"));

	if(BoxColisor)
	{
		BoxColisor->SetGenerateOverlapEvents(true);
	}

	BoxColisor->OnComponentBeginOverlap.AddDynamic(this, &ADefeatTrigger::OnDefeatTriggerOverlap);

}

void ADefeatTrigger::OnDefeatTriggerOverlap(UPrimitiveComponent* OverlappedComponent, 
										  AActor* OtherActor, 
										  UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult)
{
	WPRINT(TEXT("OVERLAP WITH DEFEAT!!"));

	// auto monster = Cast<AMonster>(OtherActor);
	// if (monster)
	// {
	// 	monster->SetWinner();
	// }
}
// Called when the game starts or when spawned
void ADefeatTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefeatTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

