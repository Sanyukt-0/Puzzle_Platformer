// Fill out your copyright notice in the Description page of Project Settings.


#include "WallGun.h"
#include "TimerManager.h"

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
	UE_LOG(LogTemp, Warning, TEXT("%s fired"), *GetName());
	//UE_LOG(LogTemp, Warning, TEXT("Fire called"));

	for (const FName& Socket : SocketNames)
	{
		FVector SocketLoc = GunMesh->GetSocketLocation(Socket);
		FRotator SocketRot = GunMesh->GetSocketRotation(Socket);

		/*UE_LOG(LogTemp, Warning, TEXT("Socket %s Rot: %s"), *Socket.ToString(), *SocketRot.ToString());*/

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		ALaser* SpawnedLaser = GetWorld()->SpawnActor<ALaser>(LaserClass, SocketLoc, SocketRot, SpawnParams);

		//UE_LOG(LogTemp, Warning, TEXT("SpawnedLaser ptr: %p"), SpawnedLaser);

		//UE_LOG(LogTemp, Warning, TEXT("Laser Owner: %s"),
		//	SpawnedLaser && SpawnedLaser->GetOwner()
		//	? *SpawnedLaser->GetOwner()->GetName()
		//	: TEXT("None"));
		//UE_LOG(LogTemp, Warning, TEXT("Spawned laser: %s"), SpawnedLaser ? TEXT("Success") : TEXT("Failed"));
		
	}

	


}


