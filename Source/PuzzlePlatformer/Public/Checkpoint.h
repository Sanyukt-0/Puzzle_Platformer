// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	UStaticMeshComponent* Checkpoint;

	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	UStaticMeshComponent* CheckpointMesh;

	UPROPERTY(EditAnywhere, Category = "Checkpoint")
	UBoxComponent* BoxComponent;

	bool bIsActivated = false;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
