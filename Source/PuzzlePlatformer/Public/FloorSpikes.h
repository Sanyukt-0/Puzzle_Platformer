// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "FloorSpikes.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API AFloorSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSpikes();

	UPROPERTY(EditAnywhere, Category = "Spikes")
	UStaticMeshComponent* FloorSpikesMesh;

	UPROPERTY(EditAnywhere, Category = "Spikes")
	UBoxComponent* SpikesCollisionBox;

	bool bOverlapped = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
