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
