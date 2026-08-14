// Fill out your copyright notice in the Description page of Project Settings.


#include "StopWallGunTrigger.h"
#include "Components/BoxComponent.h"
#include "WallGunManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AStopWallGunTrigger::AStopWallGunTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;


    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AStopWallGunTrigger::OnOverlapBegin);

}

void AStopWallGunTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
    if (!Cast<ACharacter>(OtherActor))
    {
        return;
    }

    AWallGunManager* WallGunManager =
        Cast<AWallGunManager>(
            UGameplayStatics::GetActorOfClass(
                GetWorld(),
                AWallGunManager::StaticClass()
            )
        );

    if (WallGunManager)
    {
        WallGunManager->ResetWallGuns();
    }
}



// Called when the game starts or when spawned
void AStopWallGunTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStopWallGunTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

