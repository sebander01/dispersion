// Fill out your copyright notice in the Description page of Project Settings.
#include "Enemy.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Defaults for collision
	//Find the capsule component of our enemy where we assume collision is
	EnemyCollision = FindComponentByClass<UCapsuleComponent>();

	//Bind collision to our player object that is a capsule collected in the constructor
	//Bind begin overlap event
	EnemyCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnActorBeginOverlap);
	//Bind end overlap event
	EnemyCollision->OnComponentEndOverlap.AddDynamic(this, &AEnemy::OnActorEndOverlap);

	//Get the player
	player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT(" " + this->GetActorNameOrLabel() + " " + player->GetActorNameOrLabel()));

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//	<summary>
//	Begin overlap
//	</summary>
//	<param name="overlappingComponent">The component that detected the hit</param>
//	<param name="otherActor">The other actor that was hit</param>
//	<param name="otherComponent">The overlaped component of  the other actor</param>
//	<param name="otherBodyIndex">Index of the body that was overlapped</param>
//	<param name="canSweep">If true the overlap was a moving object that used a sweep</param>
//	<param name="sweepResult">Extra information about the overlap when bFromSweep is true</param>
void AEnemy::OnActorBeginOverlap(UPrimitiveComponent* overlappingComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex, bool canSweep, const FHitResult& sweepResult)
{
	//If the tag of the colliding actor is our light tag
	if (otherActor->Tags.Contains(LightSourceTag))
	{
		//Save the coliding light source
		Light = otherActor;

		//The enemy is in light and needs to move away from it
		enemyState = EEnemyMovement::AwayFromTarget;
	}
	//If the colliding object is not a light
	else
	{
		//The enemy is not in light and should move towards the target
		enemyState = EEnemyMovement::TowardsTarget;
	}
}

//	<summary>
//	End overlap
//	</summary>
//	<param name="overlappingComponent">The component that detected the hit</param>
//	<param name="otherActor">The other actor that was hit</param>
//	<param name="otherComponent">The overlaped component of  the other actor</param>
//	<param name="otherBodyIndex">Index of the body that was overlapped</param>
//	<param name="canSweep">If true the overlap was a moving object that used a sweep</param>
//	<param name="sweepResult">Extra information about the overlap when bFromSweep is true</param>
void AEnemy::OnActorEndOverlap(UPrimitiveComponent* overlappingComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, int32 otherBodyIndex)
{
	//When our overlap of an actor ends we reset the enemy position to stationary
	enemyState = EEnemyMovement::Stationary;
}

/// <summary>
/// React to light follow the player if not in light
/// </summary>
void AEnemy::EnemyReactToLight(float EnemyContinuanceOffset)
{
	//If not in light
	if (enemyState == EEnemyMovement::TowardsTarget)
	{
		//Follow our goal object that being the player
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), player);
	}
	//If in light
	else if (enemyState == EEnemyMovement::AwayFromTarget)
	{
		//If we have a light source
		if (Light != NULL)
		{
			//Take our collision from the coliding object (Light) by grabbing the first collision
			USphereComponent* boundingBox = Light->FindComponentByClass<USphereComponent>();

			//Use the collision box to find the radius (Edge) of the sphere
			double radius = boundingBox->GetLocalBounds().GetSphere().W;

			//Take the center of the edge
			FVector center = boundingBox->GetLocalBounds().GetSphere().Center;

			//Enemy position
			FTransform enemyPos = this->GetActorTransform();

			//Now figure out what is the quicker route
			FVector goal;

			//If center is less then the enemy position the enemy is on top
			if (center.X < enemyPos.GetLocation().X)
			{
				//If enemy is on the top they should continue moving up to the edge of the sphere and then past it with our offset
				goal.X = center.X + radius + EnemyContinuanceOffset;
			}
			//If center is more then the x position of enemy the enemy is on the bottom
			else if (center.X > enemyPos.GetLocation().X)
			{
				//If enemy is on the bottom they should continue moving down to the edge of the sphere and then past it with our offset
				goal.X = center.X - radius - EnemyContinuanceOffset;
			}

			//Repeat for Y (Left and right)
			//If center is less then the enemy position the enemy is on right
			if (center.Y < enemyPos.GetLocation().Y)
			{
				//If enemy is on the right they should continue right to the edge of the sphere and then past it with our offset
				goal.Y = center.Y + radius + EnemyContinuanceOffset;
			}
			//If center is more then the Y position of enemy the enemy is on the left
			else if (center.Y > enemyPos.GetLocation().Y)
			{
				//If enemy is on the left they should continue left to the edge of the sphere and then past it with our offset
				goal.Y = center.Y - radius - EnemyContinuanceOffset;
			}

			//Goal needs a z axis we can just copy the z axis of the enemy because we can assume the enemy can walk at the elivation of the enemy
			goal.Z = enemyPos.GetLocation().Z;

			//Follow our destination out of the light
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), goal);
		}
	}
	//If the enemy shouldn't be moving only turning to the player
	else if (enemyState == EEnemyMovement::Stationary)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), this->GetActorLocation());
	}
}

