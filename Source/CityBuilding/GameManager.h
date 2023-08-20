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
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> LogsPack;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> StonesPack;
	UPROPERTY(EditAnywhere) AActor* HighLightObject;
	UPROPERTY(EditAnywhere) AActor* Grid;
	UPROPERTY(EditAnywhere) TArray<FString> InteractableTags;
#pragma endregion

	EBuildingType ToBuild;
	ACityPlayerPawn* MainPlayer;
	bool InBuildingMode = false;
	bool CanBuild = false;

	int RawWoodAmount = 0;
	int WoodAmount = 0;
	int StoneAmount = 0;
	
	void ShowGrid(bool state);
	void SpawnBuilding(EBuildingType buildingType);
	void SpawnLogs(const FVector& spawnLocation);
	void SpawnStones(const FVector& spawnLocation);
	void SpawnPack(TSubclassOf<AActor> object,const FVector& spawnLocation); 
};


