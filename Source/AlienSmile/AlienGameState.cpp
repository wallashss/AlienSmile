// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienGameState.h"

#include "AlienSmile.h"
#include "Monster.h"
#include "Engine/Blueprint.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include <Components/CapsuleComponent.h>
#include <Camera/CameraComponent.h>


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

}


void AAlienGameState::BeginPlay()
{
    Super::BeginPlay();

    WPRINT(TEXT("**************GAME START**************"))


    SpawnMonster();


}

void AAlienGameState::SetupGame(AActor * SpawnLoc, AActor * DefeatTrigger, UClass * InProjectileClass)
{
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

    if (!CurrentMonster)
    {
        WPRINT(TEXT("DID NOT FOUND OUR MONSTER"));
        return;    
    }
    WPRINT(TEXT("WE FOUND OUR MONSTER!!!!"));

    GetWorld()->GetTimerManager().SetTimer(ResetPlayerTimer, this, &AAlienGameState::ResetPlayer, 0.01f);
}

void AAlienGameState::RequestNewMonster()
{
    GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AAlienGameState::SpawnMonster, 1.0f);
    // SpawnMonster();
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

            UE_LOG(LogAlienSmile, Warning, TEXT("Cam Rot: %s"),*CamRot.ToString());
            UE_LOG(LogAlienSmile, Warning, TEXT("Pawn Rot: %s"),*Pawn->GetActorRotation().ToString());

            auto TempRot = UKismetMathLibrary::ComposeRotators(CamRot.GetInverse(), PawnRot);
            auto FinalRot = UKismetMathLibrary::ComposeRotators(PawnRot, TempRot);
            FinalRot.Roll = 0.0f;
            FinalRot.Pitch = 0.0f;
            Pawn->SetActorRotation(FinalRot);

            auto PawnLoc = Pawn->GetActorLocation();
            auto CamLoc = Cam->GetComponentLocation();

            auto Diff = CamLoc - PawnLoc;

            UE_LOG(LogAlienSmile, Warning, TEXT("Player: %s | Cam: %s | Diff: %s"), *PawnLoc.ToString(), *CamLoc.ToString(), *Diff.ToString() );
            Pawn->SetActorLocation(PawnLoc - FVector(Diff.X, Diff.Y, 0));
        
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

void AAlienGameState::SpawnMonster()
{

    // if(MonsterObject)
    // {
    //     UBlueprint* GeneratedBP = Cast<UBlueprint>(MonsterObject);

    //     if(GeneratedBP)
    //     {
    //         CurrentMonster = Cast<AMonster>(GetWorld()->SpawnActor(GeneratedBP->GeneratedClass, &SpawnLocation, &SpawnRotation));
    //         if(CurrentMonster)
    //         {
    //             // CurrentMonster->SetActorLabel(TEXT("Monster"));
    //             WPRINT(TEXT("SPAWN MONSTER"));
    //         }
    //         else
    //         {
    //             WPRINT(TEXT("FAILED TO SPAWN MONSTER: NULL"));
    //         }
    //     }
 
    // }
    if(CurrentMonster)
    {
        // CurrentMonster->MonsterDir
        CurrentMonster->MonsterDir = SpawnDir;
        CurrentMonster->MonsterRot = SpawnRotation;
        CurrentMonster->SetActorLocation(SpawnLocation);
        CurrentMonster->ResetMonster();
    }


    // auto NewMonster = 

}
