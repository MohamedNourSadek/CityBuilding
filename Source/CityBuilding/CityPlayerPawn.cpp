// Fill out your copyright notice in the Description page of Project Settings.


#include "CityPlayerPawn.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ACityPlayerPawn::ACityPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACityPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	mySprinComponent = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
}			

// Called every frame
void ACityPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(MovementInput.X != 0)
	{
		const FVector newLocation = GetActorLocation() + (GetActorRightVector() * MovementInput.X * MovementSpeed * mySprinComponent->TargetArmLength);
		SetActorLocation(newLocation);
	}

	if(MovementInput.Y != 0)
	{
		float angle = 90 - (FMath::RadiansToDegrees(FMath::Acos(GetActorForwardVector().GetSafeNormal().Dot(FVector(0,0,1).GetSafeNormal()))));
		FVector upVector = FMath::Sin(FMath::DegreesToRadians(-angle)) * FVector(0, 0, 1);
		FVector projectedForward = GetActorForwardVector() + upVector;

		FVector newLocation = GetActorLocation() + (projectedForward * MovementInput.Y * MovementSpeed * mySprinComponent->TargetArmLength);
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void ACityPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_X", this, &ACityPlayerPawn::OnMoveXPressed);
	PlayerInputComponent->BindAxis("Move_Y", this, &ACityPlayerPawn::OnMoveYPressed);
	PlayerInputComponent->BindAxis("Wheel", this, &ACityPlayerPawn::OnWheel);
	PlayerInputComponent->BindAxis("MouseX", this, &ACityPlayerPawn::OnMouseX);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Pressed, this, &ACityPlayerPawn::OnMiddleMousePressed);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Released, this, &ACityPlayerPawn::OnMiddleMouseReleased);
}

void ACityPlayerPawn::OnMoveXPressed(float value)
{
	MovementInput.X = value;
}

void ACityPlayerPawn::OnMoveYPressed(float value)
{
	MovementInput.Y = value;
}

void ACityPlayerPawn::OnWheel(float value)
{
	if(value != 0)
	{
		float increment = (-value * ZoomSpeed);
		float finalValue = mySprinComponent->TargetArmLength + increment;

		if (finalValue > ZoomLimits.Y)
		{
			mySprinComponent->TargetArmLength = ZoomLimits.Y;
		}
		else if(finalValue < ZoomLimits.X )
		{
			mySprinComponent->TargetArmLength = ZoomLimits.X;
		}
		else
		{
			mySprinComponent->TargetArmLength = finalValue;
		}
	}


}

void ACityPlayerPawn::OnMouseX(float value)
{
	if(MiddleMouseInput && value != 0)
	{
		FRotator angle(0, value * RotationSpeed, 0);
		AddActorWorldRotation(angle);
	}
}


void ACityPlayerPawn::OnMiddleMousePressed()
{
	MiddleMouseInput = true;
}

void ACityPlayerPawn::OnMiddleMouseReleased()
{
	MiddleMouseInput = false;
}



