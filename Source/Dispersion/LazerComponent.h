// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LazerComponent.generated.h"

//Forward Declaration to speed up load times
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class DISPERSION_API ALazerComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALazerComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "LazerFunction")
	void LazerFindEnd();

	UPROPERTY(EditAnywhere, Category = "LazerFunction")
	float MaxRenderDistance;

	UPROPERTY(EditAnywhere, Category = "LazerFunction")
	UStaticMeshComponent* EmitterObject;

private:
	UNiagaraComponent* LazerEffect;
};
