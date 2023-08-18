#include "CityPlayerPawn.h"

#include "Building.h"
#include "CityBuildingGameModeBase.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

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
	HandleBuildingMode();
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
	myController = Cast<APlayerController>(GetController());
	gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	ShowMouse(true);
}
void ACityPlayerPawn::AssignInputCallBacks(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Move_X", this, &ACityPlayerPawn::OnMoveXPressed);
	PlayerInputComponent->BindAxis("Move_Y", this, &ACityPlayerPawn::OnMoveYPressed);
	PlayerInputComponent->BindAxis("Wheel", this, &ACityPlayerPawn::OnWheel);
	PlayerInputComponent->BindAxis("MouseX", this, &ACityPlayerPawn::OnMouseX);
	PlayerInputComponent->BindAxis("MouseY", this, &ACityPlayerPawn::OnMouseY);
	PlayerInputComponent->BindAction("LeftMouse", IE_Pressed, this, &ACityPlayerPawn::OnLeftMousePressed);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Pressed, this, &ACityPlayerPawn::OnMiddleMousePressed);
	PlayerInputComponent->BindAction("MiddleMouse", IE_Released, this, &ACityPlayerPawn::OnMiddleMouseReleased);
	PlayerInputComponent->BindAction("Cancel", IE_Pressed, this, &ACityPlayerPawn::OnCancelPressed);
}
#pragma endregion

#pragma region Gameplay Functions
void ACityPlayerPawn::Move()
{
	if (movementInput.X != 0)
	{
		const FVector newLocation = GetActorLocation() + (GetActorRightVector() * movementInput.X * MovementSpeed * mySprinComponent->TargetArmLength);
		SetActorLocation(newLocation);
	}
	if (movementInput.Y != 0)
	{
		FVector newLocation = GetActorLocation() + (GetProjectedForward() * movementInput.Y * MovementSpeed * mySprinComponent->TargetArmLength);
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
void ACityPlayerPawn::RotateX(float delta)
{
	if(delta != 0)
	{
		FRotator angle(0, delta * RotationSpeed, 0);
		AddActorWorldRotation(angle);
	}
}
void ACityPlayerPawn::RotateY(float delta)
{
	if (delta != 0)
	{
		float angle = GetAngleWithHorizontal();

		bool outOfBoundriesPositive = angle > RotationYLimits.Y;
		bool outOfBoundriesNegative = angle < RotationYLimits.X;
		bool increasing = delta < 0;
		bool decreasing = delta > 0;

		if(!(outOfBoundriesPositive && increasing) && !(outOfBoundriesNegative && decreasing))
			AddActorLocalRotation(FRotator(delta * RotationSpeed, 0, 0));
	}
}
void ACityPlayerPawn::ShowMouse(bool state)
{
	myController->bShowMouseCursor = state;
	myController->bEnableClickEvents = state;
	myController->bEnableMouseOverEvents = state;
}
void ACityPlayerPawn::ResetMousePositionOnReachingBorder()
{
	FVector2d mousePosition;
	FVector2d screenSize;
	
	myController->GetMousePosition(mousePosition.X, mousePosition.Y);
	GEngine->GameViewport->GetViewportSize(screenSize);

	if (mousePosition.X < 10 || mousePosition.X > screenSize.X -10 )
	{
		myController->SetMouseLocation(screenSize.X/2.0, screenSize.Y / 2.0);
	}

	if (mousePosition.Y < 10 || mousePosition.Y > screenSize.Y-10)
	{
		myController->SetMouseLocation(screenSize.X / 2.0, screenSize.Y / 2.0);
	}
}
void ACityPlayerPawn::HandleBuildingMode()
{
	if(gameMode->GameManager->InBuildingMode)
	{
		buildingUnderMouse = nullptr;

		FHitResult hit = CastFromMouse();

		if (hit.bBlockingHit && IsValid(hit.GetActor()))
		{
			if (hit.GetActor()->Tags.Contains("Grid"))
			{
				gridElementSelected = hit.GetActor();
				gameMode->GameManager->HighLightObject->SetActorLocation(hit.GetActor()->GetActorLocation());
				gameMode->GameManager->HighLightObject->SetActorRotation(hit.GetActor()->GetActorRotation());
				gameMode->GameManager->CanBuild = true;
			}
			else
			{
				gameMode->GameManager->HighLightObject->SetActorLocation(FVector(0, 0, 5000000));
				gameMode->GameManager->CanBuild = false;
			}
		}
		else 
		{
			gameMode->GameManager->HighLightObject->SetActorLocation(FVector(0,0,5000000));
		}
	}
	else
	{
		gameMode->GameManager->HighLightObject->SetActorLocation(FVector(0,0,5000000));

		FHitResult hit = CastFromMouse();

		if (hit.bBlockingHit && IsValid(hit.GetActor()) )
		{
			if(hit.GetActor()->Tags.Contains("Building"))
			{
				buildingUnderMouse = Cast<ABuilding>(hit.GetActor());
			}
			else
			{
				buildingUnderMouse = nullptr;
			}
		}
	}
}
FHitResult ACityPlayerPawn::CastFromMouse()
{
	FHitResult hit;
	Cast<APlayerController>(GetController())->GetHitResultUnderCursor(ECC_WorldStatic, false, hit);
	return hit;
}
#pragma endregion 

#pragma  region Vector Math
FVector ACityPlayerPawn::GetProjectedForward()
{
	float angle = GetAngleWithHorizontal();
	FVector upVector = FMath::Sin(FMath::DegreesToRadians(angle)) * FVector(0, 0, 1);

	return GetActorForwardVector() + upVector;
}
float ACityPlayerPawn::GetAngleWithHorizontal()
{
	return - (90 - (FMath::RadiansToDegrees(FMath::Acos(GetActorForwardVector().GetSafeNormal().Dot(FVector(0, 0, 1).GetSafeNormal())))));
}
#pragma endregion

#pragma region Input Callbacks
void ACityPlayerPawn::OnMoveXPressed(float value)
{
	movementInput.X = value;
}
void ACityPlayerPawn::OnMoveYPressed(float value)
{
	movementInput.Y = value;
}
void ACityPlayerPawn::OnWheel(float value)
{
	Zoom(value);
}
void ACityPlayerPawn::OnMouseX(float value)
{
	if (middleMouseInput)
	{
		RotateX(value);
		ResetMousePositionOnReachingBorder();
	}
}
void ACityPlayerPawn::OnMouseY(float value)
{
	if (middleMouseInput)
	{
		RotateY(value);
		ResetMousePositionOnReachingBorder();
	}
}
void ACityPlayerPawn::OnLeftMousePressed()
{
	if(gameMode->GameManager->InBuildingMode && gameMode->GameManager->CanBuild)
	{
		gameMode->GameManager->SpawnBuilding(gameMode->GameManager->ToBuild);
		gridElementSelected->Destroy();

		OnCancelPressed();
	}
	else if(buildingUnderMouse != nullptr && gameMode->UIManager->IsBuildingInfoOpen == false)
	{
		gameMode->UIManager->OpenBuildingInfoPopUp(buildingUnderMouse);
	}
}
void ACityPlayerPawn::OnMiddleMousePressed()
{
	middleMouseInput = true;
	ShowMouse(false);
	myController->GetMousePosition(lastKnownMousePosition.X, lastKnownMousePosition.Y);
}
void ACityPlayerPawn::OnMiddleMouseReleased()
{
	middleMouseInput = false;
	ShowMouse(true);
	myController->SetMouseLocation(lastKnownMousePosition.X, lastKnownMousePosition.Y);
}
void ACityPlayerPawn::OnCancelPressed()
{
	if(gameMode->GameManager->InBuildingMode)
		gameMode->UIManager->GameplayView->OnCancelBuilding();
}
#pragma endregion
