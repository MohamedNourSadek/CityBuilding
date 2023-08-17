// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "BuildingInfo.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CityPlayerPawn.generated.h"

class AGameManager;

UCLASS()
class CITYBUILDING_API ACityPlayerPawn : public APawn
{
	GENERATED_BODY()

#pragma region Unreal Delegates
public:
	ACityPlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma endregion

#pragma region  Designer Variables
	UPROPERTY(EditAnywhere) FVector2D ZoomLimits;
	UPROPERTY(EditAnywhere) FVector2D RotationYLimits;
	UPROPERTY(EditAnywhere)	float MovementSpeed = 1;
	UPROPERTY(EditAnywhere) float ZoomSpeed = 1;
	UPROPERTY(EditAnywhere) float RotationSpeed = 1;
	UPROPERTY(EditAnywhere, Category = "Building") TEnumAsByte<ECollisionChannel> BuildingTraceChannelProperty = ECC_WorldStatic;
	UPROPERTY(EditAnywhere) AActor* HighLightObject;
	
#pragma endregion

#pragma region Setup Functions
	void Initialize();
	void AssignInputCallBacks(UInputComponent* PlayerInputComponent);
#pragma endregion

#pragma region Gameplay Functions
	void Move();
	void Zoom(float delta);
	void RotateX(float delta);
	void RotateY(float delta);
	void ShowMouse(bool state);
	void ResetMousePositionOnReachingBorder();
	void HandleBuildingMode();
#pragma region Vector Math
	FVector GetProjectedForward();
	float GetAngleWithHorizontal();
#pragma endregion
#pragma  endregion

#pragma region Input Callbacks
	void OnMoveXPressed(float value);
	void OnMoveYPressed(float value);
	void OnWheel(float value);
	void OnMouseX(float value);
	void OnMouseY(float value);
	void OnLeftMousePressed();
	void OnMiddleMousePressed();
	void OnMiddleMouseReleased();
	void OnCancelPressed();
#pragma endregion

#pragma region Private Variables 
private:
	USpringArmComponent* mySprinComponent;
	APlayerController* myController;
	FVector2D movementInput;
	bool middleMouseInput;
	FVector2D lastKnownMousePosition;
	AGameManager* gameManager;

public:

	UPROPERTY(EditAnywhere) TSubclassOf<class UBuildingInfo> buildingPopUpClass;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> HouseBuilding;
	UPROPERTY(EditAnywhere) TEnumAsByte<ECollisionChannel> worldCollisionChannel;
	UPROPERTY(VisibleAnywhere) ABuilding* BuildingUnderMouse;
#pragma endregion

};
