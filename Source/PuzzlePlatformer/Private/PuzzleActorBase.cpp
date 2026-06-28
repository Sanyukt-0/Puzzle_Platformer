// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleActorBase.h"

// Sets default values
APuzzleActorBase::APuzzleActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APuzzleActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuzzleActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleActorBase::Activate()
{
}

void APuzzleActorBase::Deactivate()
{
}