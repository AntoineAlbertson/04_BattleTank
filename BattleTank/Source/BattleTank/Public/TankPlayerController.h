// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	

private:
	UPROPERTY(EditAnywhere)
		float CrossAirXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
		float CrossAirYLocation = 0.3333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;

	ATank* GetControlledTank() const;
	

	void AimTowardCrossair();
	
	bool GetSighRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
};
