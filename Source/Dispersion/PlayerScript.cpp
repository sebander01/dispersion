// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScript.h"

// Sets default values
APlayerScript::APlayerScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Defaults for collision
	//Find the collision for the player object
	PlayerCollision = FindComponentByClass<UPrimitiveComponent>();
	//Make sure this is the root component
	RootComponent = PlayerCollision;

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

	//Bind collision
	//Bind hit event
	PlayerCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerScript::OnActorBeginOverlap);
	PlayerCollision->OnComponentHit.AddDynamic(this, &APlayerScript::OnHit);
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

	//Cast as EnhancedInputComponent
	UEnhancedInputComponent* CurrentInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//Sprinting control
	//Bind sprinting control when pressed down
	CurrentInputComponent->BindAction(sprint, ETriggerEvent::Started, this, &APlayerScript::EnableSprint);
	//Bind sprinting control for when released
	CurrentInputComponent->BindAction(sprint, ETriggerEvent::Completed, this, &APlayerScript::EnableSprint);

	//Bind jumping control
	CurrentInputComponent->BindAction(playerJump, ETriggerEvent::Triggered, this, &APlayerScript::PlayerJump);
}

//	<summary>
//	Collision implimentation on overlap
//	</summary>
//	<param name="overlappingComponent">The component that detected the hit</param>
//	<param name="otherActor">The other actor that was hit</param>
//	<param name="otherComponent">The overlaped component of  the other actor</param>
//	<param name="otherBodyIndex">Index of the body that was overlapped</param>
//	<param name="canSweep">If true the overlap was a moving object that used a sweep</param>
//	<param name="sweepResult">Extra information about the overlap when bFromSweep is true</param>
void APlayerScript::OnActorBeginOverlap(UPrimitiveComponent* overlappingComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool canSweep, const FHitResult& sweepResult)
{

}

//	<summary>
//	Collision implimentation on hit
//	</summary>
//	<param name="hitComponent">The component that was hit</param>
//	<param name="otherActor">The other actor that was hit</param>
//	<param name="otherComponent">The component that was hit of the actor actor</param>
//	<param name="collisionForce">The force of the collision</param>
//	<param name="hit">Information about the hit</param>
void APlayerScript::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector collisionForce, const FHitResult& hit)
{

}

/// <summary>
/// This method allows for player movement
/// </summary>
/// <param name="playerBody"></param>
void APlayerScript::PlayerMovement(FVector direction)
{
	//If sprinting
	if (sprinting)
	{
		//Move the player body based on the direction variable assigned in the blueprint
		playerBody->AddImpulse(direction * sprintSpeed);
	}
	//If not sprinting
	else
	{
		//Move the player body based on the direction variable assigned in the blueprint
		playerBody->AddImpulse(direction * playerSpeed);
	}
}

//A method to allow the player to jump
void APlayerScript::PlayerJump()
{
	//If sprinting is enabled
	if (sprinting)
	{
		//Add an upwords impulse
		playerBody->AddImpulse(FVector(0, 0, sprintJumpForce));
	}
	//If sprinting is disabled
	else
	{
		//Add an upwords inpulse
		playerBody->AddImpulse(FVector(0, 0, playerJumpForce));
	}
}

//A method to enable sprinting
void APlayerScript::EnableSprint()
{
	//If sprinting is enabled
	if (sprinting)
	{
		//Disable sprinting
		sprinting = false;
	}
	//If sprinting is disabled
	else
	{
		//Enable sprinting
		sprinting = true;
	}
}

