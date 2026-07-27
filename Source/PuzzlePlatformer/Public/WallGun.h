// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"  
#include "Laser.h"
#include "WallGun.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API AWallGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallGun();
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "Laser")
	TSubclassOf<ALaser> LaserClass;

	UPROPERTY(EditAnywhere, Category = "Laser")
	float FireInterval;

	UPROPERTY(EditAnywhere, Category = "Laser")
	float InitialDelay;

	UPROPERTY(EditAnywhere, Category = "Laser")
	TArray<FName> SocketNames;


	FTimerHandle FireTimerHandle;



};
