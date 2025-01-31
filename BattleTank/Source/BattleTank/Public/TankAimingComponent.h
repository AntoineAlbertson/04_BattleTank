// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
// Forward Declaration
class UTankTurret;
class UTankBarrel;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
		
	// Sets default values for this component's properties
	UTankAimingComponent();

	//TODO Get turret ref

	void AimingAt(FVector HitLocation,float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);
	
private:

	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);

};
