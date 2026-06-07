// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

//An enum for the states of enemy movement
UENUM(BlueprintType)
enum class EEnemyMovement : uint8
{
	Stationary UMETA(DisplayName = "Stationary"),
	TowardsTarget UMETA(DisplayName = "Towards Target"),
	AwayFromTarget UMETA(DisplayName = "Away From Target")
};

UCLASS()
class DISPERSION_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float walkingSpeed;

	UFUNCTION(BlueprintCallable, Category = "Enemy Behavior")
	void EnemyReactToLight(AActor* goalObject, float EnemyContinuanceOffset);

	//Variables for light sources
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	FName LightSourceTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TArray<AActor*> LightsInScene;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	EEnemyMovement enemyState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	AActor* Light;

};
