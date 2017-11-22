// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

#define OUT


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardCrossair();

}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Not possessing any Tank"))
	}

}

void ATankPlayerController::AimTowardCrossair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation ;

	if (GetSighRayHitLocation(HitLocation)) //Has "side effect", going to line trace and set the HitLocation
	{
		GetControlledTank()->AimAt(HitLocation);

	//Get world location if linetrace through crossair
	//If hit landscape
		//TODO Tell tank to aim at this point
	}
}

//Get world location of linetrace through crosshair, true if hit landscape

bool ATankPlayerController::GetSighRayHitLocation(FVector& OutHitLocation) const
{

	//Find Crossair position 
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossAirXLocation, ViewportSizeY * CrossAirYLocation);

	// De-project the screen position of the crossair to a world direction
	FVector LookDirection;

	if(GetLookDirection(ScreenLocation,LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return true;
		}
		
	}
	
	//Line trace along the look direction, see what we hit ( up to max range )
	//Get Look vector hit location

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CamWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CamWorldLocation,
		LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult Hit;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility ))
	{
		HitLocation = Hit.Location;
		return true;
	}
	else {
		HitLocation = FVector(0.0f);
		return false;
	}
	
}



ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());

}

