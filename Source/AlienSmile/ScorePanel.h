// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScorePanel.generated.h"

UCLASS()
class ALIENSMILE_API AScorePanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScorePanel();

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnScoreUpdate(int Score);

	UFUNCTION(BlueprintImplementableEvent, Category = "Alien")
	void OnInitScore(int Score);

	void InitScore(int Score);

	void UpdateScore(int Score);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
