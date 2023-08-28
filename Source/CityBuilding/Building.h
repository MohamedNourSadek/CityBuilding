#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

class ACityPlayerPawn;

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
	UPROPERTY(EditAnywhere) UChildActorComponent* BuildingOptionsActor;
	UPROPERTY(EditAnywhere) TEnumAsByte<EBuildingType> BuildingType;
	UPROPERTY(EditAnywhere) float AnimationSpeed = 2;
	UPROPERTY(EditAnywhere) FRuntimeFloatCurve Curve;
	UPROPERTY(EditAnywhere) float TotalTimeSinceStartUp = 0;
	UPROPERTY(EditAnywhere) float BuildingHeight = 50;
private:
	bool animatingStartAnim = true;

	ACityPlayerPawn* mainPlayer;
};

