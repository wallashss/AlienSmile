// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienGameState.h"

#include <Camera/CameraComponent.h>
#include <Components/BoxComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Engine/Blueprint.h>

#include "AlienSmile.h"
#include "DefeatTrigger.h"
#include "FunnySpawner.h"
#include "Monster.h"
#include "ScorePanel.h"
//#include "VRNotificationsComponent.h"


static const float RESET_GAME_TIMEOUT = 5.5f;
AAlienGameState::AAlienGameState()
{
    // static ConstructorHelpers::FClassFinder<AMonster> MonsterClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Monster.BP_Monster'"));
    // UObject * ClassPackage = ANY_PACKAGE;
    // MonsterObject = FindObject<UObject>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Monster.BP_Monster'"));

    // {
    //     ProjectileObject = FindObject<UObject>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/VRTemplate/Blueprints/Projectile.Projectile'"));

    //     if(ProjectileObject)
    //     {
    //         UBlueprint* GeneratedBP = Cast<UBlueprint>(ProjectileObject);
    //         ProjectileClass = GeneratedBP->GeneratedClass;
    //     }
    // }

    // if(MonsterObject)
    // {
    //     WPRINT(TEXT("GET SPAWN MONSTER CLASS"));
    // }
    // else
    // {
    //     WPRINT(TEXT("MISSED SPAWN MONSTER CLASS !!!"));
    // }

// UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("/Game/DEXIED/Foliage/Tree/BP_TreeDestroyed_Style_1.BP_TreeDestroyed_Style_1")));

// UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
    Score = 0;

}


void AAlienGameState::BeginPlay()
{
    Super::BeginPlay();

    WPRINT(TEXT("**************GAME START**************"))

    if(APlayerController * PlayerController = GetWorld()->GetFirstPlayerController())
    {
        const auto Pawn = PlayerController->GetPawn();
        OriginalPlayerPos = Pawn->GetActorLocation();
        OriginalPlayerRot = Pawn->GetActorRotation();

        // if(auto Cam = Pawn->FindComponentByClass<UCameraComponent>())
        // {
        //     OriginalPlayerPos = Cam->GetComponentLocation();
        //     OriginalPlayerRot = Cam->GetComponentRotation();
        //     UE_LOG(LogAlienSmile, Warning, TEXT("Original CAM: %s"), *OriginalPlayerPos.ToString());
        // }
    }


}

void AAlienGameState::SetupGame(AActor * SpawnLoc, AActor * GameOver)
{
    // Setup Monster
    WPRINT(TEXT("Setup Game"));
    if (SpawnLoc)
    {
        SpawnLocation = SpawnLoc->GetActorLocation();
        SpawnRotation = SpawnLoc->GetActorRotation();
        SpawnDir = SpawnLoc->GetActorForwardVector();

        SpawnTransform = SpawnLoc->GetTransform();
        WPRINT(TEXT("Setup Game Done"));
    }
    
    CurrentMonster = Cast<AMonster>(UGameplayStatics::GetActorOfClass(GetWorld(), AMonster::StaticClass()));

    if(CurrentMonster)
    {
        CurrentMonster->OnMonsterDefeated.AddDynamic(this, &AAlienGameState::OnMonsterDefeated);
    }

    if (!CurrentMonster)
    {
        WPRINT(TEXT("DID NOT FOUND OUR MONSTER"));
        return;    
    }

    // Reset Player
    GetWorld()->GetTimerManager().SetTimer(ResetPlayerTimer, this, &AAlienGameState::ResetPlayer, 0.01f);

    // Setup defeat trigger
    auto DefeatTrigger = Cast<ADefeatTrigger>(UGameplayStatics::GetActorOfClass(GetWorld(), ADefeatTrigger::StaticClass()));

    if(DefeatTrigger)
    {
        DefeatTrigger->BoxColisor->OnComponentBeginOverlap.AddDynamic(this, &AAlienGameState::OnDefeatTriggerOverlap);
    }

    // Setup Game Over
    if(GameOver)
    {
        GameOverMesh = GameOver->GetComponentByClass<UStaticMeshComponent>();
        if(!GameOverMesh)
        {
            WPRINT(TEXT("No Game Over Set!"));
        }
    }

    // Setup Score
    
    ScorePanel = Cast<AScorePanel>(UGameplayStatics::GetActorOfClass(GetWorld(), AScorePanel::StaticClass()));

    // 

    APlayerController * PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        auto Pawn = PlayerController->GetPawn(); 
        // Pawn->AddComponentByClass<UVRNotificationsComponent>();
        // auto VRNotifications = Pawn->GetComponentByClass<UVRNotificationsComponent>();

        // TSubclassOf<UActorComponent> Class, bool bManualAttachment, const FTransform& RelativeTransform, bool bDeferredFinish
        // Pawn->AddComponentByClass<UVRNotificationsComponent>(UVRNotificationsComponent::StaticClass, true, GetTransform(), false);
        // const auto VRNotification = Pawn->GetComponentByClass<UVRNotificationsComponent>();

        // if(VRNotification)
        // {
            
        // }
        // UVRNotificationsComponent* VRNotification = NewObject<UVRNotificationsComponent>(Pawn);

        // VRNotification->HMDPutOnHeadDelegate.AddDynamic(this, &AAlienGameState::ResumeGame);

        // VRNotification->HMDRemovedFromHeadDelegate.AddDynamic(this, &AAlienGameState::PauseGame);

        // VRNotification->HMDRecenteredDelegate.AddDynamic(this, &AAlienGameState::ResetPlayer);

        // CurrentMonster->SetTarget(Pawn->GetActorLocation());

    }

}

void AAlienGameState::PauseGame()
{
    UE_LOG(LogAlienSmile, Warning, TEXT("REQUEST PAUSE GAME!"));
    APlayerController * PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->Pause();
    }

}

void AAlienGameState::ResumeGame()
{
    UE_LOG(LogAlienSmile, Warning, TEXT("REQUEST RESUME GAME!"));
    APlayerController * PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->SetPause(false);
    }
    
}


void AAlienGameState::InitGame()
{
    // Setup score
    Score = 0;
    if (ScorePanel)
    {
        ScorePanel->InitScore(Score);
    }

    // Respawn Monster
    RequestNewMonster();

    // Setup Spawners
    TArray<AActor*> Spawners;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFunnySpawner::StaticClass(), Spawners);

    for(auto a : Spawners)
    {
        if(auto s = Cast<AFunnySpawner>(a))
        {
            s->StartSpawn();

            FunnyIndicesCount = s->Objects.Num();
            UE_LOG(LogAlienSmile, Warning, TEXT("Init Game / s->Objects.Num(): %d "), s->Objects.Num());
        }
    }

    


    // Broadcast Game start
    OnGameStart.Broadcast();
}

void AAlienGameState::ResetGame()
{
    UGameplayStatics::OpenLevel(this, FName(TEXT("LevelAlien")));
}

void AAlienGameState::OnMonsterDefeated()
{
    RequestNewMonster();

    OnScoreUp.Broadcast();

    Score++;
    if(ScorePanel)
    {
        ScorePanel->UpdateScore(Score);
    }
}

void AAlienGameState::RequestNewMonster()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AAlienGameState::SpawnMonster, 1.0f);
}

FTransform AAlienGameState::GetSpawnTransform()
{
    return SpawnTransform;
}

void AAlienGameState::ResetPlayer()
{
    APlayerController * PlayerController = GetWorld()->GetFirstPlayerController();
    if(PlayerController)
    {
        auto Pawn = PlayerController->GetPawn(); 
        auto Cam = Pawn->FindComponentByClass<UCameraComponent>();

        if (Cam)
        {
            auto CamRot = Cam->GetComponentRotation();
            auto PawnRot = Pawn->GetActorRotation();

            auto TempRot = UKismetMathLibrary::ComposeRotators(CamRot.GetInverse(), OriginalPlayerRot);
            auto FinalRot = UKismetMathLibrary::ComposeRotators(PawnRot, TempRot);
            FinalRot.Roll = 0.0f;
            FinalRot.Pitch = 0.0f;
            Pawn->SetActorRotation(FinalRot);

            auto PawnLoc = Pawn->GetActorLocation();
            auto CamLoc = Cam->GetComponentLocation();
            auto Diff = OriginalPlayerPos - CamLoc;

            Pawn->SetActorLocation(PawnLoc + FVector(Diff.X, Diff.Y, 0));        
        }
        else
        {
            WPRINT(TEXT("NO CAMERA"));
        }
    }
    else
    {
        WPRINT(TEXT("NO PLAYER LOC????"));
    }
}


void AAlienGameState::OnDefeatTriggerOverlap(UPrimitiveComponent* OverlappedComponent, 
										  AActor* OtherActor, 
										  UPrimitiveComponent* OtherComp, 
										  int32 OtherBodyIndex, 
										  bool bFromSweep, 
										  const FHitResult & SweepResult)
{
	WPRINT(TEXT("GAME STATE: OVERLAP WITH DEFEAT!!"));

	auto Monster = Cast<AMonster>(OtherActor);
	if (Monster)
	{
		Monster->SetWinner();
        SetGameOver();
	}
}


void AAlienGameState::SetGameOver()
{
    // If you would like to do something with this event
    OnGameOver.Broadcast();

    if(GameOverMesh)
    {
        GameOverMesh->SetVisibility(true);
    }
    else
    {
        WPRINT(TEXT("No Game Over instance!"));
    }

    GetWorldTimerManager().SetTimer(ResetGameTimer, this, &AAlienGameState::ResetGame, RESET_GAME_TIMEOUT);
    // ResetGameTimer
}

void AAlienGameState::SpawnMonster()
{
    if(CurrentMonster)
    {
        // Increase difficult
        if( Score > 0 && Score % 3 == 0)
        {
            CurrentMonster->IncreaseSpeed(50.0f);
        }
        CurrentMonster->MonsterDir = SpawnDir;
        CurrentMonster->MonsterRot = SpawnRotation;
        CurrentMonster->SetActorLocation(SpawnLocation);
        CurrentMonster->ResetMonster();
        CurrentMonster->FunnyIdx = FMath::RandRange(0, FunnyIndicesCount - 1);

        UE_LOG(LogAlienSmile, Warning, TEXT("Monster IDX: %d"), CurrentMonster->FunnyIdx);
    }
    else
    {
        WPRINT(TEXT("NO MONSTER"));
    }

}
