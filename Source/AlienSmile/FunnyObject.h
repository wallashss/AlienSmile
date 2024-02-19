// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FunnyObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALIENSMILE_API UFunnyObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFunnyObject();

public:

	UFUNCTION()
	void Disapear();

	UFUNCTION()
	void SetActivated();

public:
	UPROPERTY(EditAnywhere)
	bool Activated;

	UPROPERTY(EditAnywhere)
	int32 FunnyIndex;

	float MaxTime;

	FTimerHandle ToDieTimer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
