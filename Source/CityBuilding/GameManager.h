#pragma once

#include "CoreMinimal.h"
#include "GameplayUIManager.h"
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

	UPROPERTY(EditAnywhere) TSubclassOf<class UGameplayUIManager> gameplayUIclass;
	UGameplayUIManager* gameplayUIManager;
	ACityPlayerPawn* mainPlayer;

	UPROPERTY(EditAnywhere)
	bool inBuildingMode = false;
};
