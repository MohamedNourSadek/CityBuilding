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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayView> GameplayViewClass;
	UGameplayView* GameplayView;
	ACityPlayerPawn* MainPlayer;

	UPROPERTY(EditAnywhere)
	bool InBuildingMode = false;
	bool IsBuildingInfoOpen = false;
};
