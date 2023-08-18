#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "GameplayView.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

class ACityPlayerPawn;

UCLASS()
class CITYBUILDING_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma region Public References
public:
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> HouseBuilding;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> TowerBuilding;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> WoodMill;
	UPROPERTY(EditAnywhere) AActor* HighLightObject;
	UPROPERTY(EditAnywhere) AActor* Grid;

#pragma endregion

	EBuildingType ToBuild;
	ACityPlayerPawn* MainPlayer;
	bool InBuildingMode = false;
	bool CanBuild = false;

	void ShowGrid(bool state);
	void SpawnBuilding(EBuildingType buildingType);
};


