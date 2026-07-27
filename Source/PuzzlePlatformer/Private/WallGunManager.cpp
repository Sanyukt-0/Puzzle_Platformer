// Fill out your copyright notice in the Description page of Project Settings.


#include "WallGunManager.h"
#include "Kismet/GameplayStatics.h" 
#include "WallGun.h"
#include "Algo/RandomShuffle.h"

// Sets default values
AWallGunManager::AWallGunManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallGunManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWallGun::StaticClass(), FoundActors);

	for (AActor* Actor : FoundActors)
	{
		AWallGun* WallGun = Cast<AWallGun>(Actor);

		if (WallGun)
		{
			WallGuns.Add(WallGun);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Found %d Wall Guns"), WallGuns.Num());

	GetWorldTimerManager().SetTimer(RandomFireTimerHandle, this, &AWallGunManager::FireRandomGuns, 2.0f, true);
	

}

void AWallGunManager::FireRandomGuns()
{
	UE_LOG(LogTemp, Warning, TEXT("FireRandomGuns called"));

	if (WallGuns.Num() == 0)
	{
		return;
	}

	int32 NumToFire = FMath::RandRange(2, 3);
	Algo::RandomShuffle(WallGuns);

	for (int i = 0; i < NumToFire; i++) {
		UE_LOG(LogTemp, Warning, TEXT("Firing gun %d"), i);
		WallGuns[i]->Fire();
	}
}

// Called every frame
void AWallGunManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

