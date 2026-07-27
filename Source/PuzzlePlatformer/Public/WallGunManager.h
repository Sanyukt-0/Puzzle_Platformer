// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallGunManager.generated.h"

class AWallGun;

UCLASS()
class PUZZLEPLATFORMER_API AWallGunManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallGunManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<AWallGun*> WallGuns;

	FTimerHandle RandomFireTimerHandle;

	void FireRandomGuns();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
