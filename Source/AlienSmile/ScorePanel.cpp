// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePanel.h"

// Sets default values
AScorePanel::AScorePanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AScorePanel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScorePanel::UpdateScore(int Score)
{
	OnScoreUpdate(Score);
}

void AScorePanel::InitScore(int Score)
{
	OnInitScore(Score);
}


