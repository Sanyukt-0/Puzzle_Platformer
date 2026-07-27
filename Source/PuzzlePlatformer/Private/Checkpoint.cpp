// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "PuzzlePlatformerGameMode.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Checkpoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint"));
	RootComponent = Checkpoint;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetGenerateOverlapEvents(true);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsActivated) return;

	APuzzlePlatformerGameMode* GameMode = Cast<APuzzlePlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint Saved!"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Checkpoint Saved!"));
		//GameMode->SetCheckpoint(GetActorLocation());
		bIsActivated = true;
	}
	

}


// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
