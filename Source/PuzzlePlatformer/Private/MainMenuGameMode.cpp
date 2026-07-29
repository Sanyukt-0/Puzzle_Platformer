// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void AMainMenuGameMode::BeginPlay()
{
	if (MainMenuWidgetClass) {
		UUserWidget* Menu = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
		
		if (Menu)
		{
			Menu->AddToViewport();
			APlayerController* PC = GetWorld()->GetFirstPlayerController();

			if (PC)
			{
				PC->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				PC->SetInputMode(InputMode);
			}
		}

	}
}