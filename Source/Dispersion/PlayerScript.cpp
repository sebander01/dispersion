// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScript.h"

// Sets default values
APlayerScript::APlayerScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerScript::BeginPlay()
{
	Super::BeginPlay();

	//Enable the player controls
	//Get the player controller
	playerCon = GetWorld()->GetFirstPlayerController();

	//Check that the player controller is valid and that there is an input mapping to apply
	if (playerCon && map_NormalGameplay != NULL)
	{
		//Using the enhancedinput subsystem bind the mapping context to the player controller enabling controls via this input method
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer())->AddMappingContext(map_NormalGameplay, 0);
	}

	//On begin play get the player movement component
	playerBody = GetCharacterMovement();
	
}

// Called every frame
void APlayerScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/// <summary>
/// This method allows for player movement
/// </summary>
/// <param name="playerBody"></param>
void APlayerScript::PlayerMovement(FVector direction)
{
	//Move the player body based on the direction variable assigned in the blueprint
	playerBody->AddImpulse(direction * playerSpeed);
}

