// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget>MainMenuWidgetClass;
};
