#include "MainPawnCharacter.h"
#include "MainPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AMainPawnCharacter::AMainPawnCharacter()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComponent);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	CapsuleComponent->SetupAttachment(SceneComponent);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(SceneComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));

	bIsGround = false;
	bUseGravity = true;
	Mass = 80.0f;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.75f;
	CharacterSpeed = NormalSpeed;

	PrimaryActorTick.bCanEverTick = true;
}

void AMainPawnCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Controller)
	{
		FRotator ControlRot = Controller->GetControlRotation();
		FRotator YawOnlyRot(0.0f, ControlRot.Yaw, 0.0f);
		SetActorRotation(YawOnlyRot);
	}

	//AddGravity();
}

void AMainPawnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (AMainPlayerController* PlayerController = Cast<AMainPlayerController>(GetController())) {
			if (PlayerController->MoveAction) {
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AMainPawnCharacter::Move
				);
			}

			if (PlayerController->LookAction) {
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AMainPawnCharacter::Look
				);
			}

			if (PlayerController->SprintAction) {
				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Triggered,
					this,
					&AMainPawnCharacter::StartSprint
				);

				EnhancedInput->BindAction(
					PlayerController->SprintAction,
					ETriggerEvent::Completed,
					this,
					&AMainPawnCharacter::EndSprint
				);
			}
		}
	}
}

void AMainPawnCharacter::Move(const FInputActionValue& value) {
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X)) {
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}
	if (!FMath::IsNearlyZero(MoveInput.Y)) {
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}
void AMainPawnCharacter::Look(const FInputActionValue& value) {
	const FVector2D LookInput = value.Get<FVector2D>();

	// Yaw: 도리도리
	AddControllerYawInput(LookInput.X);
	// Pitch: 끄덕끄덕
	AddControllerPitchInput(LookInput.Y);
}
void AMainPawnCharacter::StartSprint(const FInputActionValue& value) {
	CharacterSpeed = NormalSpeed * SprintSpeedMultiplier;
}
void AMainPawnCharacter::EndSprint(const FInputActionValue& value) {
	CharacterSpeed = NormalSpeed;
}
/*
void AMainPawnCharacter::AddGravity()
{
	if (!bUseGravity || bIsGround)return;
	FVector GravityForce = FVector(0.0f, 0.0f, -Mass * Gravity);
	AddMovementInput(GravityForce);
}
*/