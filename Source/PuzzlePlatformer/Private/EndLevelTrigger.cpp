// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "PuzzlePlatformerCharacter.h"
#include "PuzzlePlatformerGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEndLevelTrigger::AEndLevelTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelTrigger::OnOverlapBegin);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEndLevelTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggered) return;

	bTriggered = true;

	APuzzlePlatformerCharacter* Player = Cast<APuzzlePlatformerCharacter>(OtherActor);

	if (Player) {
		APuzzlePlatformerGameMode* GameMode = Cast<APuzzlePlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (GameMode) {
			GameMode->ShowThanksForPlaying();
			TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

// Called when the game starts or when spawned
void AEndLevelTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEndLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

