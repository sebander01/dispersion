// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
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

#pragma region Public Collision functions and properties

	//Important for my future to explain why UFUNCTION() is used here and why not using it was a mistake
	//UFUNCTION() is needed to interact with unreal things because it creates a header without this unreal thinks it does not exist 
	//and for this reason UFUNCTION() must be used when creating OnHit or OnActorBeginOverlap because even though we aren't calling it in blueprint
	//it is directly interacting with parts of the engine that require it. Without it OnHit and OnActorBeginOverlap will simply do nothing.
	//Not because it's broken but because unreal does not know that it should do anything with them at all.

	UFUNCTION()
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

	UFUNCTION()
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
	UCapsuleComponent* PlayerCollision;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	FString jumpResetTag;

#pragma endregion

#pragma region Public Player Movement
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

#pragma endregion


#pragma region Public Controls and input actions
	UPROPERTY(EditAnywhere, Category = "Input Mapping")
	//Input action sprint
	UInputAction* sprint;

	UPROPERTY(EditAnywhere, Category = "Input Mapping")
	//Input action jumping
	UInputAction* playerJump;

	//The input mapping for player
	UPROPERTY(EditAnywhere, Category = "Input Mapping");
	UInputMappingContext* map_NormalGameplay;
#pragma endregion

private:
	//A variable to hold the player controller
	APlayerController* playerCon;

	//Is springing bool
	bool sprinting;

	//A variable to decide if a player can jump
	bool canJump;
};
