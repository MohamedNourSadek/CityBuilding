// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "CityBuildingGameModeBase.h"
#include "GameplayView.h"
#include "BuildingInfoView.h"
#include "Obstacle.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	InitializeUI();
}
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AUIManager::InitializeUI()
{
	Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->UIManager = this;

	GameplayView = CreateWidget<UGameplayView>(GetGameInstance(), GameplayViewClass);
	GameplayView->AddToViewport();
}
void AUIManager::OpenBuildingInfoPopUp(ABuilding* building)
{
	const auto buildingPopUp = CreateWidget<UBuildingInfoView>(GetGameInstance(), buildingPopUpClass);
	buildingPopUp->AddToViewport();
	buildingPopUp->SetUI(building->BuildingType);

	GameplayView->SetAllVisibility(false);
	IsBuildingInfoOpen = true;
}
void AUIManager::ShowHoverUI(bool state, AActor* actor)
{
	if(state)
	{
		AObstacle* obstacle = Cast<AObstacle>(actor);;

		if(ResourcesHoverView != nullptr)
		{
			ResourcesHoverView->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			ResourcesHoverView = CreateWidget<UResourceHover>(GetGameInstance(), ResourceHoverClass);
			ResourcesHoverView->AddToViewport();
		}

		if(obstacle != nullptr)
			ResourcesHoverView->SetUIUp(obstacle->Resources);
	}
	else
	{
		if(ResourcesHoverView != nullptr)
		{
			ResourcesHoverView->SetVisibility (ESlateVisibility::Hidden);
		}
	}
}

