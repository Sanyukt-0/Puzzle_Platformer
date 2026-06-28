// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "RotatingLaser.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API ARotatingLaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARotatingLaser();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		UStaticMeshComponent* LaserMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		UStaticMeshComponent* LaserBeamMesh;

		UBoxComponent* LaserCollision;
		
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		float RotationSpeed;

		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
