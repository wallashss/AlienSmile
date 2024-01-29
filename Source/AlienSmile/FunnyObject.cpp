// Fill out your copyright notice in the Description page of Project Settings.


#include "FunnyObject.h"

// Sets default values for this component's properties
UFunnyObject::UFunnyObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Activated = false;
	// ...

	

}

void UFunnyObject::Disapear()
{
	GetOwner()->Destroy();
}

// Called when the game starts
void UFunnyObject::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->GetWorldTimerManager().SetTimer(ToDieTimer, this, &UFunnyObject::Disapear, 1200.0f, false);
	// ...
	// GetActor
	
}


// Called every frame
void UFunnyObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

