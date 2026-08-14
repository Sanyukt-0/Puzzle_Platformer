// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActorBase.h"
#include "SciFiSlidingDoor.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API ASciFiSlidingDoor : public APuzzleActorBase
{
	GENERATED_BODY()

public:
	ASciFiSlidingDoor();
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* LeftDoor;

	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* RightDoor;

	FVector LeftStartLocation;
	FVector RightStartLocation;

	FVector LeftEndLocation;
	FVector RightEndLocation;

	UPROPERTY(EditAnywhere, Category = "Door")
	FVector LeftOpenOffset;

	UPROPERTY(EditAnywhere, Category = "Door")
	FVector RightOpenOffset;

	bool bIsMoving;
	bool bIsReversing;
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* OpenSound;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* CloseSound;
	
};
