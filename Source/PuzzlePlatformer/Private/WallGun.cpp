// Fill out your copyright notice in the Description page of Project Settings.


#include "WallGun.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
AWallGun::AWallGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	RootComponent = GunMesh;

}

// Called when the game starts or when spawned
void AWallGun::BeginPlay()
{
	Super::BeginPlay();
	//GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AWallGun::Fire, FireInterval, true, InitialDelay);
	
}

void AWallGun::Fire()
{
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}

	for (const FName& Socket : SocketNames)
	{
		FVector SocketLoc = GunMesh->GetSocketLocation(Socket);
		FRotator SocketRot = GunMesh->GetSocketRotation(Socket);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ALaser* SpawnedLaser = GetWorld()->SpawnActor<ALaser>(LaserClass, SocketLoc, SocketRot, SpawnParams);

	}

	


}


