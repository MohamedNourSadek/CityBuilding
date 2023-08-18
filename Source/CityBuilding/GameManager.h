#pragma once

#include "CoreMinimal.h"
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
	UPROPERTY(EditAnywhere) AActor* HighLightObject;
#pragma endregion

	ACityPlayerPawn* MainPlayer;
	bool InBuildingMode = false;
};
