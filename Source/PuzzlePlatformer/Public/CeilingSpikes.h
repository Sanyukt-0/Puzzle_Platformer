// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CeilingSpikes.generated.h"

UENUM()
enum class ESpikesState : uint8
{
	Idle,
	Dropping,
	Extended,
	Retracting
};

UCLASS()
class PUZZLEPLATFORMER_API ACeilingSpikes : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACeilingSpikes();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SpikeMesh;

	ESpikesState CurrentState;
	FVector OriginalLocation;
	float DropSpeed;
	float RetractSpeed;

	FTimerHandle DelayTimerHandle;

	FTimerHandle RetractTimerHandle;

	FTimerHandle RespawnDelayHandle;

	UPROPERTY(EditAnywhere, Category = "Trigger")
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void StartDrop();
	void StartRetract();
	void ResetSpikes();

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
