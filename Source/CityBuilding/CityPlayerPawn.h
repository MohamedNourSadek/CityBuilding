// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CityPlayerPawn.generated.h"

UCLASS()
class CITYBUILDING_API ACityPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACityPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnMoveXPressed(float value);
	void OnMoveYPressed(float value);
	void OnWheel(float value);
	void OnMouseX(float value);
	void OnMiddleMousePressed();
	void OnMiddleMouseReleased();


	FVector2D MovementInput;
	bool MiddleMouseInput;

	UPROPERTY(EditAnywhere)	float MovementSpeed = 1;
	UPROPERTY(EditAnywhere) float ZoomSpeed = 1;
	UPROPERTY(EditAnywhere) float RotationSpeed = 1;
	UPROPERTY(EditAnywhere) FVector2D ZoomLimits;
	UPROPERTY(EditAnywhere) USpringArmComponent* mySprinComponent;
};
