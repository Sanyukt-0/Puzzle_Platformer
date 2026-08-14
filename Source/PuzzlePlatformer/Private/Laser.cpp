// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "PuzzlePlatformerGameMode.h"

// Sets default values
ALaser::ALaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;

	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	LaserMesh->SetupAttachment(CollisionBox);

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);

	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);

	CollisionBox->SetGenerateOverlapEvents(true);

	LaserMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALaser::OnOverlapBegin);

}

void ALaser::DestroySelf()
{
	Destroy();
}

void ALaser::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character)
	{
		if(ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}

		APuzzlePlatformerGameMode* GameMode = GetWorld()->GetAuthGameMode<APuzzlePlatformerGameMode>();
		if (GameMode)
		{
			GameMode->KillAndRespawnPlayer(Character);
		}
		Destroy();
	}
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();

	LaserMesh->SetSimulatePhysics(false);
	LaserMesh->SetEnableGravity(false);
	
	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ALaser::DestroySelf, 5.0f, false);

	SetActorTickEnabled(true);
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + FVector(GetActorForwardVector() * Speed * DeltaTime);

	FHitResult Hit;
	SetActorLocation(NewLocation, true, &Hit);


	if (Hit.bBlockingHit)
	{
		Destroy();
		return;
	}
	
}

