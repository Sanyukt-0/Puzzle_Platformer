// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActorBase.h"
#include "Components/BoxComponent.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API APressurePlate : public APuzzleActorBase
{
	GENERATED_BODY()
	
public:
	APressurePlate();
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
	UStaticMeshComponent* PressurePlateMesh;
protected:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
	TArray<APuzzleActorBase*> TargetActors;



};
