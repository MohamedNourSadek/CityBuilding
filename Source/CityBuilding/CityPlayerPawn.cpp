#include "CityPlayerPawn.h"

#pragma region Unreal Delegates
ACityPlayerPawn::ACityPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ACityPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}			
void ACityPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}
void ACityPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	AssignInputCallBacks(PlayerInputComponent);
}
#pragma endregion

#pragma region Setup Functions
void ACityPlayerPawn::Initialize()
{
	mySprinComponent = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
}
void ACityPlayerPawn::AssignInputCallBacks(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Move_X", this, &ACityPlayerPawn::OnMoveXPressed);
	PlayerInputComponent->BindAxis("Move_Y", this, &ACityPlayerPawn::OnMoveYPressed);
	PlayerInputComponent->BindAxis("Wheel", this, &ACityPlayerPawn::OnWheel);
	PlayerInputComponent->BindAxis("MouseX", this, &ACityPlayerPawn::OnMouseX);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Pressed, this, &ACityPlayerPawn::OnMiddleMousePressed);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Released, this, &ACityPlayerPawn::OnMiddleMouseReleased);
}
#pragma endregion

#pragma region Gameplay Functions
void ACityPlayerPawn::Move()
{
	if (MovementInput.X != 0)
	{
		const FVector newLocation = GetActorLocation() + (GetActorRightVector() * MovementInput.X * MovementSpeed * mySprinComponent->TargetArmLength);
		SetActorLocation(newLocation);
	}
	if (MovementInput.Y != 0)
	{
		FVector newLocation = GetActorLocation() + (GetProjectedForward() * MovementInput.Y * MovementSpeed * mySprinComponent->TargetArmLength);
		SetActorLocation(newLocation);
	}
}
void ACityPlayerPawn::Zoom(float delta)
{
	if(delta != 0)
	{
		float increment = (-delta * ZoomSpeed);
		float finalValue = mySprinComponent->TargetArmLength + increment;

		if (finalValue > ZoomLimits.Y)
		{
			mySprinComponent->TargetArmLength = ZoomLimits.Y;
		}
		else if (finalValue < ZoomLimits.X)
		{
			mySprinComponent->TargetArmLength = ZoomLimits.X;
		}
		else
		{
			mySprinComponent->TargetArmLength = finalValue;
		}
	}
}
void ACityPlayerPawn::Rotate(float delta)
{
	if(delta != 0)
	{
		FRotator angle(0, delta * RotationSpeed, 0);
		AddActorWorldRotation(angle);
	}
}


FVector ACityPlayerPawn::GetProjectedForward()
{
	float angle = 90 - (FMath::RadiansToDegrees(FMath::Acos(GetActorForwardVector().GetSafeNormal().Dot(FVector(0, 0, 1).GetSafeNormal()))));
	FVector upVector = FMath::Sin(FMath::DegreesToRadians(-angle)) * FVector(0, 0, 1);

	return GetActorForwardVector() + upVector;
}
#pragma endregion

#pragma region Input Callbacks
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
	Zoom(value);
}
void ACityPlayerPawn::OnMouseX(float value)
{
	if(MiddleMouseInput)
		Rotate(value);
}
void ACityPlayerPawn::OnMiddleMousePressed()
{
	MiddleMouseInput = true;
}
void ACityPlayerPawn::OnMiddleMouseReleased()
{
	MiddleMouseInput = false;
}
#pragma endregion
