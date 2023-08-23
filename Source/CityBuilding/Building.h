// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UENUM()
enum EBuildingType
{
	House UMETA(DisplayName = "House"),
	WoodMill UMETA(DisplayName = "WoodMill"),
	Tower UMETA(DisplayName = "Tower")
};

UCLASS()
class CITYBUILDING_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuilding();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere) TEnumAsByte<EBuildingType> BuildingType;
	UPROPERTY(EditAnywhere) float AnimationSpeed = 2;
	
private:
	bool animatingStartAnim = true;
};

