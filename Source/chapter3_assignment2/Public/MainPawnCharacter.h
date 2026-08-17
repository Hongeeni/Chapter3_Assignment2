#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainPawnCharacter.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UCharacterMovementComponent;
struct FInputActionValue;

UCLASS()
class CHAPTER3_ASSIGNMENT2_API AMainPawnCharacter : public APawn
{
	GENERATED_BODY()

public:
	AMainPawnCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Character")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
