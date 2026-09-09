// Fill out your copyright notice in the Description page of Project Settings.

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "LazerComponent.h"

// Sets default values
ALazerComponent::ALazerComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALazerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	//Find the niagra component on the object so we don't have to assign it manually when there is only 1 instance
	try
	{	//Assign the object
		LazerEffect = FindComponentByClass<UNiagaraComponent>();
	}
	//If we can't find it
	catch (const std::exception&)
	{
		//Produce an error
		UE_LOG(LogTemp, Error, TEXT("There is no LazerEffect attached to %s"), *this->GetName())
	}

	//Find the end of our lazer
	LazerFindEnd();
}

// Called every frame
void ALazerComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//A method to find the end of the given lazer and make the visual match
void ALazerComponent::LazerFindEnd()
{
	//A variable to hold our hit result
	FHitResult hit;
	//Trace the line by channel
	if (GetWorld()->LineTraceSingleByChannel(hit, EmitterObject->GetForwardVector(), FVector(EmitterObject->GetForwardVector().X, EmitterObject->GetForwardVector().Y, MaxRenderDistance), ECC_Visibility))
	{
		//Make the lazer effect end where the trace hit's the object to create the effect of an endless lazer
		LazerEffect->SetNiagaraVariableVec3(TEXT("User.BeamEnd"), hit.ImpactPoint);
	}
}

