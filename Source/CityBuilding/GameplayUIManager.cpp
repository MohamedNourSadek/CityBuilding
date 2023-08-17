// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUIManager.h"

#include "CityBuildingGameModeBase.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UGameplayUIManager::NativeConstruct()
{
	Super::Construct();

	BuildButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnBuildButtonClick);
	BackButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnBackButtonClick);
	HouseButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnHouseButtonClick);
	CancelBuilding->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnCancelBuilding);

	GetGameManager();

	Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameplayUIManager = this;
}

void UGameplayUIManager::SetAllVisibility(bool state)
{
	if(state)
		AllUnits->SetVisibility(ESlateVisibility::Visible);
	else
		AllUnits->SetVisibility(ESlateVisibility::Hidden);
}


void UGameplayUIManager::OnBuildButtonClick() 
{
	GameplayUI->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);
}

void UGameplayUIManager::OnBackButtonClick()
{
	GameplayUI->SetVisibility(ESlateVisibility::Visible);
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
}

void UGameplayUIManager::OnHouseButtonClick()
{
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
	Building->SetVisibility(ESlateVisibility::Visible);

	if(GameManager == nullptr)
		GetGameManager();

	GameManager->InBuildingMode = true;
}

void UGameplayUIManager::OnCancelBuilding()
{
	Building->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);

	if (GameManager == nullptr)
		GetGameManager();

	GameManager->InBuildingMode = false;
	GameManager->IsBuildingInfoOpen = false;
}

void UGameplayUIManager::GetGameManager()
{
	GameManager = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->GameManager;
}


