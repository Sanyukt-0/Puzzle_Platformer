// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "WeightedPressurePlate.h"

APressurePlate::APressurePlate()
{
	
	PressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PressurePlateMesh"));
	RootComponent = PressurePlateMesh;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(PressurePlateMesh);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);

	TargetActors = TArray<APuzzleActorBase*>();
}

void APressurePlate::Activate()
{


	for (APuzzleActorBase* Actor : TargetActors)
	{
		if (Actor)
		{
			Actor->Activate();
		}
	}


}


void APressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Activate();
}

void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}