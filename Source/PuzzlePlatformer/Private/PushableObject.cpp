// Fill out your copyright notice in the Description page of Project Settings.


#include "PushableObject.h"

// Sets default values
APushableObject::APushableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PushableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PushableMesh"));
	RootComponent = PushableMesh;

	// enable physics simulation for the mesh
	PushableMesh->SetSimulatePhysics(true);

	PrimaryActorTick.bCanEverTick = true;
}

void APushableObject::BeginPlay() {
	Super::BeginPlay();
}

void APushableObject::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
