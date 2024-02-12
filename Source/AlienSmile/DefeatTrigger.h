// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefeatTrigger.generated.h"

UCLASS()
class ALIENSMILE_API ADefeatTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefeatTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnDefeatTriggerOverlap(UPrimitiveComponent* OverlappedComponent, 
										  AActor* OtherActor, 
										  UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult);

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent * BoxColisor;


};
