// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayView.h"
#include "CityBuildingGameModeBase.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UGameplayView::NativeConstruct()
{
	Super::Construct();

	BuildButton->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnBuildButtonClick);
	BackButton->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnBackButtonClick);
	HouseButton->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnHouseButtonClick);
	CancelBuilding->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnCancelBuilding);

	gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->UIManager->GameplayView = this;
}

void UGameplayView::SetAllVisibility(bool state)
{
	if (state)
		AllUnits->SetVisibility(ESlateVisibility::Visible);
	else
		AllUnits->SetVisibility(ESlateVisibility::Hidden);
}

void UGameplayView::OnBuildButtonClick()
{
	GameplayUI->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);
}

void UGameplayView::OnBackButtonClick()
{
	GameplayUI->SetVisibility(ESlateVisibility::Visible);
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
}

void UGameplayView::OnHouseButtonClick()
{
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
	Building->SetVisibility(ESlateVisibility::Visible);


	gameMode->GameManager->InBuildingMode = true;
}

void UGameplayView::OnCancelBuilding()
{
	Building->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);

	gameMode->GameManager->InBuildingMode = false;
	gameMode->UIManager->IsBuildingInfoOpen = false;
}

