// Fill out your copyright notice in the Description page of Project Settings.


#include "SciFiSlidingDoor.h"

ASciFiSlidingDoor::ASciFiSlidingDoor()
{
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));

	LeftDoor->SetupAttachment(DoorFrame);
	RightDoor->SetupAttachment(DoorFrame);

	bIsMoving = false;
	bIsReversing = false;
	MoveSpeed = 200.f;
	PrimaryActorTick.bCanEverTick = true;
}

void ASciFiSlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving) {
		FVector LeftCurrentLocation = LeftDoor->GetRelativeLocation();
		FVector RightCurrentLocation = RightDoor->GetRelativeLocation();

		FVector LeftNewLocation = FMath::VInterpConstantTo(LeftCurrentLocation, LeftEndLocation, DeltaTime, MoveSpeed);
		FVector RightNewLocation = FMath::VInterpConstantTo(RightCurrentLocation, RightEndLocation, DeltaTime, MoveSpeed);

		LeftDoor->SetRelativeLocation(LeftNewLocation);
		RightDoor->SetRelativeLocation(RightNewLocation);

		if (LeftNewLocation.Equals(LeftEndLocation, 3.0f) && RightNewLocation.Equals(RightEndLocation, 3.0f)) {
			/*LeftDoor->SetRelativeLocation(LeftNewLocation);
			RightDoor->SetRelativeLocation(RightNewLocation);*/
			bIsMoving = false;
		}
		
	}

	else if(bIsReversing)
	{
		FVector LeftCurrentLocation = LeftDoor->GetRelativeLocation();
		FVector RightCurrentLocation = RightDoor->GetRelativeLocation();

		FVector LeftNewLocation = FMath::VInterpConstantTo(LeftCurrentLocation, LeftStartLocation, DeltaTime, MoveSpeed);
		FVector RightNewLocation = FMath::VInterpConstantTo(RightCurrentLocation, RightStartLocation, DeltaTime, MoveSpeed);

		LeftDoor->SetRelativeLocation(LeftNewLocation);
		RightDoor->SetRelativeLocation(RightNewLocation);

		if (LeftNewLocation.Equals(LeftStartLocation, 3.0f) && RightNewLocation.Equals(RightStartLocation, 3.0f)) {
			/*LeftDoor->SetRelativeLocation(LeftNewLocation);
			RightDoor->SetRelativeLocation(RightNewLocation);*/
			bIsReversing = false;
		}
	}
}

void ASciFiSlidingDoor::Activate()
{
	bIsReversing = false;
	bIsMoving = true;
}

void ASciFiSlidingDoor::Deactivate()
{
	bIsMoving = false;
	bIsReversing = true;
}

void ASciFiSlidingDoor::BeginPlay()
{
	Super::BeginPlay();
	LeftStartLocation = LeftDoor->GetRelativeLocation();
	RightStartLocation = RightDoor->GetRelativeLocation();

	LeftEndLocation = LeftStartLocation + LeftOpenOffset;
	RightEndLocation = RightStartLocation + RightOpenOffset;
}
