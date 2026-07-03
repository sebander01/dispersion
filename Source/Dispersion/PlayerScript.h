// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
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

	UFUNCTION(BlueprintCallable, Category = "Player Movement")
	void PlayerMovement(FVector direction);

	UCharacterMovementComponent* playerBody;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
	float playerSpeed;

	//The input mapping for player
	UPROPERTY(EditAnywhere, Category = "Input Mapping");
	UInputMappingContext* map_NormalGameplay;
private:
	//A variable to hold the player controller
	APlayerController* playerCon;
};
