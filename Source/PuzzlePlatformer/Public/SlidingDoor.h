// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "SlidingDoor.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API ASlidingDoor : public APuzzleActorBase
{
	GENERATED_BODY()

public:
	ASlidingDoor();
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Door")
	UStaticMeshComponent* DoorMesh;

	FVector StartLocation;

	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Door")
	FVector OpenOffset;

	bool bIsMoving;
	float MoveSpeed;
};
