// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FakePlatform.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API AFakePlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFakePlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Mesh")
	UStaticMeshComponent* PlatformMesh;

	FVector OriginalLocation;

	FTimerHandle FallTimerHandle;
	FTimerHandle ResetTimerHandle;

	bool bIsTriggered;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void TriggerFall();
	void ResetPlatform();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
