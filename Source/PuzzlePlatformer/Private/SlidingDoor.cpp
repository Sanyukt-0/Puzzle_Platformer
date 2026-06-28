// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"

ASlidingDoor::ASlidingDoor() 
{
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	bIsMoving = false;
	MoveSpeed = 200.f;
	PrimaryActorTick.bCanEverTick = true;
}

void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsMoving)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, EndLocation, DeltaTime, MoveSpeed);
		SetActorLocation(NewLocation);
		if (NewLocation.Equals(EndLocation, 3.0f)) {

			SetActorLocation(EndLocation);
			bIsMoving = false;
		}
	}
}

void ASlidingDoor::Activate()
{
	bIsMoving = true;
}

void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + GetActorForwardVector() * OpenOffset.X + GetActorRightVector() * OpenOffset.Y + GetActorUpVector() * OpenOffset.Z;
}
