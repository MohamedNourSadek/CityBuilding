// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Building.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UCLASS()
class CITYBUILDING_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AUIManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

#pragma region Private Functions
private:
	void InitializeUI();

#pragma endregion 

#pragma region Public Functions
public:
	void OpenBuildingInfoPopUp(ABuilding* building);
#pragma endregion 

#pragma region UI Classes
	UPROPERTY(EditAnywhere)	TSubclassOf<class UGameplayView> GameplayViewClass;
	UPROPERTY(EditAnywhere) TSubclassOf<class UBuildingInfoView> buildingPopUpClass;
#pragma endregion 

#pragma region Global UI References
public:
	UGameplayView* GameplayView;
	bool IsBuildingInfoOpen = false;
#pragma endregion

};
