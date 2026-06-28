// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushableObject.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API APushableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Pushabell Object")
	UStaticMeshComponent* PushableMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
