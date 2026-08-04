// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EndLevelTrigger.generated.h"

UCLASS()
class PUZZLEPLATFORMER_API AEndLevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndLevelTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bTriggered = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
