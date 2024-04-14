// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocityHelper.h"


// static const MAX_SIZ

static const float UPDATE_INTERVAL = 0.250f;
// Sets default values for this component's properties
UVelocityHelper::UVelocityHelper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UVelocityHelper::BeginPlay()
{
	Super::BeginPlay();

	// ...

	GetWorld()->GetTimerManager().SetTimer(LastPosTimer, this, &UVelocityHelper::OnPosUpdate, UPDATE_INTERVAL);
	
}

void UVelocityHelper::OnPosUpdate()
{
	const auto NewPos = GetOwner()->GetActorLocation();
	CurrentVelocity = NewPos - LastPos;
	LastPos = NewPos; 
}


