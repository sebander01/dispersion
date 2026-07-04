// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerScript.generated.h"

UCLASS()
class DISPERSION_API APlayerScript : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerScript();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//	<summary>
	//	Collision implimentation on overlap
	//	</summary>
	//	<param name="overlappingComponent">The component that detected the hit</param>
	//	<param name="otherActor">The other actor that was hit</param>
	//	<param name="otherComponent">The overlaped component of  the other actor</param>
	//	<param name="otherBodyIndex">Index of the body that was overlapped</param>
	//	<param name="canSweep">If true the overlap was a moving object that used a sweep</param>
	//	<param name="sweepResult">Extra information about the overlap when bFromSweep is true</param>
	void OnActorBeginOverlap(UPrimitiveComponent* overlappingComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool canSweep, const FHitResult& sweepResult);

	//	<summary>
	//	Collision implimentation on hit
	//	</summary>
	//	<param name="hitComponent">The component that was hit</param>
	//	<param name="otherActor">The other actor that was hit</param>
	//	<param name="otherComponent">The component that was hit of the actor actor</param>
	//	<param name="collisionForce">The force of the collision</param>
	//	<param name="hit">Information about the hit</param>
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector collisionForce, const FHitResult& hit);

	//Collision for player
	UPrimitiveComponent* PlayerCollision;


	//A method to enable sprinting
	void EnableSprint();

	UFUNCTION(BlueprintCallable, Category = "Player Movement")
	void PlayerMovement(FVector direction);

	UCharacterMovementComponent* playerBody;

	//Player movement speed
	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float playerSpeed;

	//Player sprint speed
	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float sprintSpeed;

	//Player Jump Function
	void PlayerJump();

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float playerJumpForce;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float sprintJumpForce;

	UPROPERTY(EditAnywhere, Category = "Input Mapping")
	//Input action sprint
	UInputAction* sprint;

	UPROPERTY(EditAnywhere, Category = "Input Mapping")
	//Input action jumping
	UInputAction* playerJump;

	//The input mapping for player
	UPROPERTY(EditAnywhere, Category = "Input Mapping");
	UInputMappingContext* map_NormalGameplay;

private:
	//A variable to hold the player controller
	APlayerController* playerCon;

	//Is springing bool
	bool sprinting;
};
