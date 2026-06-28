// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzlePlatformerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PuzzlePlatformer.h"

APuzzlePlatformerCharacter::APuzzlePlatformerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)


	JumpCount = 0;
	MaxJump = 2;

}

void APuzzlePlatformerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APuzzlePlatformerCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APuzzlePlatformerCharacter::DoJumpEnd);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APuzzlePlatformerCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &APuzzlePlatformerCharacter::Look);

		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APuzzlePlatformerCharacter::DoSprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APuzzlePlatformerCharacter::DoSprintEnd);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APuzzlePlatformerCharacter::Look);

		}
	else
	{
		UE_LOG(LogPuzzlePlatformer, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APuzzlePlatformerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void APuzzlePlatformerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void APuzzlePlatformerCharacter::StartWallRun()
{
	if (bIsWallRunning) {
		return;
	}
	if (bWallRunCooldown) return;

	bIsWallRunning = true;
	GetCharacterMovement()->GravityScale = 0.0f;
	WallRunTimer = 0.0f;
}

void APuzzlePlatformerCharacter::StopWallRun()
{
	bWallRunCooldown = true;
	GetWorldTimerManager().SetTimer(WallRunCooldownTimer, [this]() {
		bWallRunCooldown = false;
		}, 0.5f, false);

	bIsWallRunning = false;
	GetCharacterMovement()->GravityScale = 1.0f;
}

void APuzzlePlatformerCharacter::UpdateWallRun(float DeltaTime)
{
	WallRunTimer += DeltaTime;

	FHitResult WallHit;


	if(GetWorld()->LineTraceSingleByChannel(WallHit, GetActorLocation(), GetActorLocation() + (GetActorRightVector() * (WallSide == EWallSide::Left ? -1 : 1) * 50.0f), ECC_Visibility))
	{
		if (!WallHit.bBlockingHit) {
			StopWallRun();
			return;
		}
	}
	else
	{
		StopWallRun();
		return;
	}

	if (WallRunTimer > 2.0f) {
		StopWallRun();
	}

	if (GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero()) {

		GetCharacterMovement()->GravityScale = 1.0f;
		return;
	}

	GetCharacterMovement()->GravityScale =0.0f;
	
	FVector RunDirection = FVector::CrossProduct(WallNormal, FVector::UpVector);
	RunDirection = (WallSide == EWallSide::Left) ? RunDirection : -RunDirection;
	GetCharacterMovement()->Velocity = RunDirection * 600.0f;
}

void APuzzlePlatformerCharacter::MoveBlockedBy(const FHitResult& Impact)
{	
	if (bIsGravityFlipped) return;

	WallNormal = Impact.Normal;

	float res = FVector::DotProduct(GetActorRightVector(), WallNormal);

	if (res > 0) {
		WallSide = EWallSide::Left;
	}
	else {
		WallSide = EWallSide::Right;
	}

	if ((GetCharacterMovement()->IsFalling()) && FVector::DotProduct(GetCharacterMovement()->Velocity, WallNormal) < 0) {
		StartWallRun();
	}
}

// TODO: Fix movement orientation when gravity is flipped
// TODO: Add inverted animation state in Animation Blueprint
void APuzzlePlatformerCharacter::DoGravityFlip()
{
	if (bIsGravityFlipCooldown) return;

	if (!bIsGravityFlipped) {
		GetCharacterMovement()->GravityScale = -1.0f;
		LaunchCharacter(FVector(0.0f, 0.0f, 100.0f), false, true);
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		bIsGravityFlipped = true;
	}
	else {
		GetCharacterMovement()->GravityScale = 1.0f;
		GetMesh()->SetRelativeRotation(FRotator(0.0f, 0.0f, -90.0f));
		bIsGravityFlipped = false;
	}

	bIsGravityFlipCooldown = true;
	GetWorldTimerManager().SetTimer(GravityFlipCooldownTimer, [this]() {
		bIsGravityFlipCooldown = false;
		}, 0.5f, false);
}


void APuzzlePlatformerCharacter::StopGravityFlip()
{
}

void APuzzlePlatformerCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void APuzzlePlatformerCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void APuzzlePlatformerCharacter::DoJumpStart()
{
	// signal the character to jump
	float horizontalForce = 800.0f;
	float verticalForce = 500.0f;

	if (bIsWallRunning) {
		FVector JumpDirection = FVector::CrossProduct(WallNormal, FVector::UpVector);
		JumpDirection = (WallSide == EWallSide::Left) ? JumpDirection : -JumpDirection;
		//LaunchCharacter(((JumpDirection * horizontalForce) + (FVector::UpVector * verticalForce)), true, true);
		LaunchCharacter((WallNormal * horizontalForce) + (FVector::UpVector * verticalForce), true, true);

		StopWallRun();
		JumpCount++;
		return;
	}


	if (JumpCount < MaxJump) {

		JumpCurrentCount = 0;
		JumpMaxCount = 2;

		Super::Jump();
		JumpCount++;
	}

		
}

void APuzzlePlatformerCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();

}

void APuzzlePlatformerCharacter::Landed(const FHitResult& Hit)
{

	Super::Landed(Hit);
	JumpCount = 0;
}

void APuzzlePlatformerCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if(bIsWallRunning)
	{
		UpdateWallRun(DeltaTime);
	}
}

void APuzzlePlatformerCharacter::DoSprintStart()
{
	if (!GetVelocity().IsNearlyZero()) {

		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void APuzzlePlatformerCharacter::DoSprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
}
