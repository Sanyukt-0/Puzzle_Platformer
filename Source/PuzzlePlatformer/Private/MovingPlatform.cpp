// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	RootComponent = PlatformMesh;

	bIsMoving = false;
	MoveSpeed = 200.f;
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsMoving) 
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, MoveSpeed);
		SetActorLocation(NewLocation);

		if (FVector::Dist(CurrentLocation, EndLocation) < 1.0f) {
			SetActorLocation(EndLocation);
			bIsMoving = false;
		}
	}

	
}

void AMovingPlatform::Activate()
{
	bIsMoving = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + GetActorForwardVector() * MoveOffset.X + GetActorRightVector() * MoveOffset.Y + GetActorUpVector() * MoveOffset.Z;

	if (bStartInvisible)
	{
		PlatformMesh->SetHiddenInGame(true);
	}
}