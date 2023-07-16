// Fill out your copyright notice in the Description page of Project Settings.


#include "CityPlayerPawn.h"

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
	
}

// Called every frame
void ACityPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(Input.X != 0)
	{
		const FVector newLocation = GetActorLocation() + FVector(0, Input.X * MovementSpeed, 0);
		SetActorLocation(newLocation);
	}

	if(Input.Y != 0)
	{
		const FVector newLocation = GetActorLocation() + FVector(Input.Y * MovementSpeed,0, 0);
		SetActorLocation(newLocation);
	}
}

// Called to bind functionality to input
void ACityPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_X", this, &ACityPlayerPawn::OnMoveXPressed);
	PlayerInputComponent->BindAxis("Move_Y", this, &ACityPlayerPawn::OnMoveYPressed);
}

void ACityPlayerPawn::OnMoveXPressed(float value)
{
	Input.X = value;
	UE_LOG(LogTemp, Display, TEXT("Move X value %f"), value);
}

void ACityPlayerPawn::OnMoveYPressed(float value)
{
	Input.Y = value;
	UE_LOG(LogTemp, Display, TEXT("Move Y value %f"), value);
}



