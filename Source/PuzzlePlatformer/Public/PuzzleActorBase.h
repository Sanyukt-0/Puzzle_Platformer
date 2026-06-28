// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleActorBase.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API APuzzleActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleActorBase();
	virtual void Tick(float DeltaTime) override;

	virtual void Activate();
	virtual void Deactivate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
};
