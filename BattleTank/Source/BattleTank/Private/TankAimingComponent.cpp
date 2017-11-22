// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



void UTankAimingComponent::AimingAt(FVector HitLocation,float LaunchSpeed)
{
	if(!Barrel){
		UE_LOG(LogTemp, Error, TEXT("No Barrel"))
			return;
	}
	if (!Turret) {
		UE_LOG(LogTemp, Error, TEXT("No Turret"))
			return;
	}
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName{ "BarrelEnd" });
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace

	);

	//Calculate the OutLaunchVelocity
	if (bHaveAimSolution) 
	{
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();

	MoveBarrelTowards(AimDirection);

	}
	else{
		UE_LOG(LogTemp, Error, TEXT("No Aim found"))
	}
	

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	//auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString())

		Barrel->Elevate(5); //TODO remove magic number

}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}
