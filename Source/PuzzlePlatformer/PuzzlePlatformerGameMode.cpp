// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformerGameMode.h"
#include "WallGunManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Blueprint/UserWidget.h"
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
            Pawn->TeleportTo(LevelStartLocation, Pawn->GetActorRotation());
        }
    }
}

void APuzzlePlatformerGameMode::KillAndRespawnPlayer(ACharacter* Character)
{
    if (!Character) return;

    AWallGunManager* WallGunManager =
        Cast<AWallGunManager>(
            UGameplayStatics::GetActorOfClass(
                GetWorld(),
                AWallGunManager::StaticClass()
            )
        );

    if (WallGunManager)
    {
        WallGunManager->ResetWallGuns();
    }

    if (!Character) return;

    CachedCharacter = Character;
    Character->GetCharacterMovement()->DisableMovement();

    GetWorldTimerManager().SetTimer(RespawnDelayHandle, this, &APuzzlePlatformerGameMode::FinishRespawn, 0.8f, false);
}

void APuzzlePlatformerGameMode::TogglePauseMenu()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();

    if (!UGameplayStatics::IsGamePaused(GetWorld()))
    {
        UGameplayStatics::SetGamePaused(GetWorld(), true);

        if (!PauseMenuWidget && PauseMenuWidgetClass)
        {
            PauseMenuWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
        }

        if (PauseMenuWidget)
        {
            PauseMenuWidget->AddToViewport();
        }
        if (PC)
        {
            PC->bShowMouseCursor = true;
            PC->SetInputMode(FInputModeUIOnly());
		}
    }

    else
    {
        UGameplayStatics::SetGamePaused(GetWorld(), false);
        if (PauseMenuWidget)
        {
            PauseMenuWidget->RemoveFromParent();
        }
        if (PC)
        {
            PC->bShowMouseCursor = false;
            PC->SetInputMode(FInputModeGameOnly());
        }
	}
}

void APuzzlePlatformerGameMode::ReturnToMainMenu()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
    if (PauseMenuWidget)
    {
       PauseMenuWidget->RemoveFromParent();
	}

    UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
}

void APuzzlePlatformerGameMode::ShowThanksForPlaying()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if(!ThanksForPlayingWidget && ThanksForPlayingWidgetClass)
    {
        ThanksForPlayingWidget = CreateWidget<UUserWidget>(GetWorld(), ThanksForPlayingWidgetClass);
	}

    if (ThanksForPlayingWidget)
    {
        ThanksForPlayingWidget->AddToViewport();
    }
    if (PC)
    {
        PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());

        ACharacter* Character = Cast<ACharacter>(PC->GetPawn());

        if (Character)
        {
            Character->GetCharacterMovement()->DisableMovement();
        }
    }

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

