// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "VelocityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALIENSMILE_API UVelocityComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVelocityComponent();

	UFUNCTION(BlueprintCallable)
	FVector GetCurrentVelocity();
	
	UFUNCTION()
	void OnPosUpdate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
	FVector LastPos;

	UPROPERTY(EditAnywhere, Category = "Alien")
	FVector CurrentVelocity;
	FTimerHandle LastPosTimer;
		
};
