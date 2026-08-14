// Fill out your copyright notice in the Description page of Project Settings.


#include "CeilingSpikes.h"
#include "PuzzlePlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ACeilingSpikes::ACeilingSpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
	RootComponent = SpikeMesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACeilingSpikes::OnOverlapBegin);

	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	DamageBox->SetupAttachment(RootComponent);

	DamageBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DamageBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	DamageBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ACeilingSpikes::OnDamageOverlap);


	SpikeMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpikeMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	CurrentState = ESpikesState::Idle;
	DropSpeed = 800.0f;
	RetractSpeed = 200.0f;
}

// Called when the game starts or when spawned
void ACeilingSpikes::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("CeilingSpikes BeginPlay"));
	OriginalLocation = GetActorLocation();
	
}

void ACeilingSpikes::StartDrop()
{
	if (DropSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),DropSound,GetActorLocation());
	}

	CurrentState = ESpikesState::Dropping;
	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &ACeilingSpikes::StartRetract, 1.0f, false);
}


void ACeilingSpikes::StartRetract()
{
	CurrentState = ESpikesState::Retracting;
	GetWorldTimerManager().SetTimer(RetractTimerHandle, this, &ACeilingSpikes::ResetSpikes, 2.0f);
}

void ACeilingSpikes::ResetSpikes()
{
	CurrentState = ESpikesState::Idle;
	SetActorLocation(OriginalLocation);
}

void ACeilingSpikes::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentState == ESpikesState::Idle)
	{
		StartDrop();
		return;
	}

}

void ACeilingSpikes::OnDamageOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (CurrentState == ESpikesState::Dropping)
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);

		if (!Character) return;

		APuzzlePlatformerGameMode* GameMode = GetWorld()->GetAuthGameMode<APuzzlePlatformerGameMode>();
		if (GameMode)
		{
			GameMode->RespawnPlayer(Character->GetController());
		}

		ResetSpikes();
	}
}

// Called every frame
void ACeilingSpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick running, State: %d"), (int)CurrentState);

	if (CurrentState == ESpikesState::Dropping)
	{
		FVector NewLocation = GetActorLocation() + FVector(0, 0, -DropSpeed * DeltaTime);
		SetActorLocation(NewLocation, false);

	}
	else if (CurrentState == ESpikesState::Retracting) {

		FVector NewLocation = GetActorLocation() + FVector(0, 0, RetractSpeed * DeltaTime);
		SetActorLocation(NewLocation, false);
		if (FVector::Dist(NewLocation, OriginalLocation) < 10.0f) {
			ResetSpikes();
		}
		
	}

}

