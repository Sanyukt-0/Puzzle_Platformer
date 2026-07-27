// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"
#include "GameFramework/Character.h"
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
	//UE_LOG(LogTemp, Warning, TEXT("Actor: %s"),
	//	OtherActor ? *OtherActor->GetName() : TEXT("None"));

	//UE_LOG(LogTemp, Warning, TEXT("Component: %s"),
	//	OtherComp ? *OtherComp->GetName() : TEXT("None"));

	if (OtherActor == GetOwner())
	{
		return;
	}

	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (Character)
	{
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
	//UE_LOG(LogTemp, Warning, TEXT("Laser BeginPlay"));

	LaserMesh->SetSimulatePhysics(false);
	LaserMesh->SetEnableGravity(false);
	
	GetWorldTimerManager().SetTimer(LifetimeTimerHandle, this, &ALaser::DestroySelf, 5.0f, false);

	SetActorTickEnabled(true);
	//UE_LOG(LogTemp, Warning, TEXT("Can Ever Tick: %d  Tick Enabled: %d"),
	//	PrimaryActorTick.bCanEverTick,
	//	IsActorTickEnabled());
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
	

	/*if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor: %s"),
			*Hit.GetActor()->GetName());

		UE_LOG(LogTemp, Warning, TEXT("Component: %s"),
			*Hit.GetComponent()->GetName());

		Destroy();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Laser Loc: %s"), *GetActorLocation().ToString());*/
}

