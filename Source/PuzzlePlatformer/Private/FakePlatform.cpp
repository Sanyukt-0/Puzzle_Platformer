// Fill out your copyright notice in the Description page of Project Settings.


#include "FakePlatform.h"

// Sets default values
AFakePlatform::AFakePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	PlatformMesh->OnComponentHit.AddDynamic(this, &AFakePlatform::OnHit);

	PlatformMesh->SetSimulatePhysics(false);

	PlatformMesh->SetNotifyRigidBodyCollision(true);

	bIsTriggered = false;


}

// Called when the game starts or when spawned
void AFakePlatform::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();

	
}

void AFakePlatform::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsTriggered) return;
	bIsTriggered = true;
	GetWorldTimerManager().SetTimer(FallTimerHandle, this, &AFakePlatform::TriggerFall, 0.75f, false);
}

void AFakePlatform::TriggerFall()
{
	PlatformMesh->SetSimulatePhysics(true);
	GetWorldTimerManager().SetTimer(ResetTimerHandle, this, &AFakePlatform::ResetPlatform, 3.0f, false);
}

void AFakePlatform::ResetPlatform()
{
	PlatformMesh->SetSimulatePhysics(false);
	SetActorLocation(OriginalLocation);
	bIsTriggered = false;
}

// Called every frame
void AFakePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

