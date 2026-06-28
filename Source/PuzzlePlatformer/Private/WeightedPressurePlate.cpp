// Fill out your copyright notice in the Description page of Project Settings.


#include "WeightedPressurePlate.h"


AWeightedPressurePlate::AWeightedPressurePlate()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	WeightedPressurePlateMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeightedPressurePlateMeshBase"));
	WeightedPressurePlateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeightedPressurePlateMesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	RootComponent = Root;
	WeightedPressurePlateMeshBase->SetupAttachment(Root);
	WeightedPressurePlateMesh->SetupAttachment(WeightedPressurePlateMeshBase);
	TriggerBox->SetupAttachment(Root);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AWeightedPressurePlate::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AWeightedPressurePlate::OnOverlapEnd);

	TargetActors = TArray<APuzzleActorBase*>();

}


void AWeightedPressurePlate::Activate()
{
	for(APuzzleActorBase* Actor : TargetActors)
	{
		if (Actor) {
			Actor->Activate();
		}
	}
}

void AWeightedPressurePlate::Deactivate()
{
	for(APuzzleActorBase* Actor : TargetActors)
	{
		if (Actor) {
			Actor->Deactivate();
		}
	}
}

void AWeightedPressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Activate();
}

void AWeightedPressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Deactivate();
}