// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformerGameMode.h"

APuzzlePlatformerGameMode::APuzzlePlatformerGameMode()
{
	// stub
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}

