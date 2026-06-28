// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingLaser.h"
#include "PuzzlePlatformerGameMode.h"

// Sets default values
ARotatingLaser::ARotatingLaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	RootComponent = LaserMesh;

	LaserBeamMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserBeamMesh"));
	LaserBeamMesh->SetupAttachment(LaserMesh);

	LaserCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LaserCollision"));
	LaserCollision->SetupAttachment(LaserBeamMesh);

	LaserCollision->OnComponentBeginOverlap.AddDynamic(this, &ARotatingLaser::OnOverlapBegin);
}


void ARotatingLaser::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (Pawn) {
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		
		if (PC) {
			APuzzlePlatformerGameMode* GameMode = Cast<APuzzlePlatformerGameMode>(GetWorld()->GetAuthGameMode());
			if (GameMode) {
				//GameMode->RespawnPlayer(PC);
			}
		}
	}
}



// Called when the game starts or when spawned
void ARotatingLaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator CurrentRotation = GetActorRotation();
	CurrentRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(CurrentRotation);
}

