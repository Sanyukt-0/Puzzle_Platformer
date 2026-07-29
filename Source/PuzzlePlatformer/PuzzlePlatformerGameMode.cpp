// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformerGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

APuzzlePlatformerGameMode::APuzzlePlatformerGameMode()
{
	// stub
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }


}

void APuzzlePlatformerGameMode::RespawnPlayer(AController* PlayerController)
{
    if (PlayerController)
    {
        APawn* Pawn = PlayerController->GetPawn();
        if (Pawn) {
			//UE_LOG(LogTemp, Warning, TEXT("Respawning player to start location: %s"), *LevelStartLocation.ToString());
            Pawn->TeleportTo(LevelStartLocation, Pawn->GetActorRotation());
        }
    }
}

void APuzzlePlatformerGameMode::KillAndRespawnPlayer(ACharacter* Character)
{
    if (!Character) return;

    CachedCharacter = Character;
    Character->GetCharacterMovement()->DisableMovement();

    GetWorldTimerManager().SetTimer(RespawnDelayHandle, this, &APuzzlePlatformerGameMode::FinishRespawn, 1.0f, false);
}

void APuzzlePlatformerGameMode::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC) {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }



	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (Pawn) {
        LevelStartLocation = Pawn->GetActorLocation();
    }
}

void APuzzlePlatformerGameMode::FinishRespawn()
{
    if (!CachedCharacter) return;

    RespawnPlayer(CachedCharacter->GetController());
    CachedCharacter->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

