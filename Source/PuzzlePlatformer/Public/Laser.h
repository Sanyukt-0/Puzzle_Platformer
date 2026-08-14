// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"   
#include "Components/StaticMeshComponent.h"
#include "Laser.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Laser")
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Laser")
	UStaticMeshComponent* LaserMesh;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float Speed;

	FTimerHandle LifetimeTimerHandle;

	void DestroySelf();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
