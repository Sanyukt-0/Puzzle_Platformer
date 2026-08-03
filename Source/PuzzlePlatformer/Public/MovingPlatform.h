// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AMovingPlatform : public APuzzleActorBase
{
	GENERATED_BODY()

public: 
	AMovingPlatform();
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	//virtual void Deactivate() override;


protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Platform")
	UStaticMeshComponent* PlatformMesh;

	FVector StartLocation;
	FVector EndLocation;

	bool bIsMoving;
	bool bIsReversing;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Platform")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category = "Platform")
	bool bStartInvisible = false;
};
