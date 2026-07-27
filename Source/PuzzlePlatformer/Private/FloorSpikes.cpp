// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSpikes.h"
#include "GameFramework/Character.h"
#include "PuzzlePlatformerGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AFloorSpikes::AFloorSpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FloorSpikesMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSpikesMesh"));
	RootComponent = FloorSpikesMesh;
	SpikesCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpikesCollisionBox"));
	SpikesCollisionBox->SetupAttachment(RootComponent);

	FloorSpikesMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	FloorSpikesMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	SpikesCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpikesCollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpikesCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	SpikesCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSpikes::OnOverlapBegin);

}


void AFloorSpikes::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Floor spikes touched!"));
	//UE_LOG(LogTemp, Warning, TEXT("Overlap fired, bOverlapped = %s"), bOverlapped ? TEXT("true") : TEXT("false"));

	if (bOverlapped) return;
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	//UE_LOG(LogTemp, Warning, TEXT("Cast result: %s"), Character ? TEXT("Success") : TEXT("Failed"));

	if (!Character) return;
	bOverlapped = true;

	APuzzlePlatformerGameMode* GameMode = GetWorld()->GetAuthGameMode<APuzzlePlatformerGameMode>();
	if (GameMode)
	{
		GameMode->KillAndRespawnPlayer(Character);
	}

	FTimerHandle ResetHandle;
	GetWorldTimerManager().SetTimer(ResetHandle, [this]() { bOverlapped = false; }, 1.1f, false);
}


// Called when the game starts or when spawned
void AFloorSpikes::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorSpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

