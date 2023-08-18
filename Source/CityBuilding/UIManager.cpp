// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "CityBuildingGameModeBase.h"
#include "GameplayView.h"
#include "BuildingInfoView.h"
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
	GameplayView->SetAllVisibility(false);
	IsBuildingInfoOpen = true;
}

