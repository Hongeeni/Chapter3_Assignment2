#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainPawnCharacter.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class USpringArmComponent;
class UFloatingPawnMovement;
struct FInputActionValue;

UCLASS()
class CHAPTER3_ASSIGNMENT2_API AMainPawnCharacter : public APawn
{
	GENERATED_BODY()

	float NormalSpeed;
	float SprintSpeedMultiplier;

public:
	AMainPawnCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Character")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Character")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

protected:
	bool bIsGround;
	bool bUseGravity;
	float Mass;
	
	const float Gravity = 980;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void EndSprint(const FInputActionValue& value);

	//void AddGravity();
};
