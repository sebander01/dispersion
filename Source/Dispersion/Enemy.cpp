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
	//Get all the light sources in the scene
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), LightSourceTag, LightsInScene);
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

/// <summary>
/// React to light follow the player if not in light
/// </summary>
void AEnemy::EnemyReactToLight(AActor* goalObject, float EnemyContinuanceOffset)
{
	//If not in light
	if (isLight == false)
	{
		//Follow our goal object that being the player
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), goalObject);
	}
	//If in light
	else
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
}

