// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay Reporting"))

		auto ControlledTank = GetControlledTank();

	if (!ControlledTank) {
		UE_LOG(LogTemp, Error, TEXT("Not possessing any Tank"))
	}
	else { UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *(ControlledTank->GetName())) }

}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());

}

