// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocityComponent.h"

#include "AlienSmile.h"
static const float UPDATE_INTERVAL = 0.050f;

// Sets default values for this component's properties
UVelocityComponent::UVelocityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UVelocityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	LastPos = GetComponentLocation();
	GetWorld()->GetTimerManager().SetTimer(LastPosTimer, this, &UVelocityComponent::OnPosUpdate, UPDATE_INTERVAL, true);
}


FVector UVelocityComponent::GetCurrentVelocity()
{
	return CurrentVelocity;
}


void UVelocityComponent::OnPosUpdate()
{
	const auto NewPos = GetComponentLocation();
	CurrentVelocity = (NewPos - LastPos) / UPDATE_INTERVAL;
	UE_LOG(LogAlienSmile, Warning, TEXT("%s %s %s"), *NewPos.ToString(), *LastPos.ToString(), *CurrentVelocity.ToString());
	LastPos = NewPos; 

}


