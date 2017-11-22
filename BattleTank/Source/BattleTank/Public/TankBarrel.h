// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"
/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max down speed, +1 is max up speed
	void Elevate(float RelativeSpeed);


private:

	UPROPERTY(EditAnywhere, Category = Properties)
		float MaxDegreesPerSeconds = 5.0f;

	UPROPERTY(EditAnywhere, Category = Properties)
		float MaxElevation = 30.0f;

	UPROPERTY(EditAnywhere, Category = Properties)
		float MinElevation = -2.0f;
};
