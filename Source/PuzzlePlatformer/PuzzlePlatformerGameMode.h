// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Character.h" 
#include "PuzzlePlatformerGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS()
class PUZZLEPLATFORMER_API APuzzlePlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	/** Constructor */
	APuzzlePlatformerGameMode();

	FVector LevelStartLocation;

	void RespawnPlayer(AController* PlayerController);

	void KillAndRespawnPlayer(ACharacter* Character);

protected:
	void BeginPlay() override;
	
	UFUNCTION()
	void FinishRespawn();

	FTimerHandle  RespawnDelayHandle;
	ACharacter* CachedCharacter;
};




