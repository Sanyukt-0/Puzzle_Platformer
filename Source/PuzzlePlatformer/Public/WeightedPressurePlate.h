// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleActorBase.h"
#include "Components/BoxComponent.h"
#include "WeightedPressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMER_API AWeightedPressurePlate : public APuzzleActorBase
{
	GENERATED_BODY()

public:
	AWeightedPressurePlate();
	//virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	virtual void Deactivate() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Plate")
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Plate")
	UStaticMeshComponent* WeightedPressurePlateMeshBase;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Plate")	
	UStaticMeshComponent* WeightedPressurePlateMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pressure Plate")
	UBoxComponent* TriggerBox;

	

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
	TArray<APuzzleActorBase*> TargetActors;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
