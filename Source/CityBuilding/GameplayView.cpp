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
	TowerButton->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnTowerButtonClick);
	WoodMillButton->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnWoodMillButtonClick);
	CancelBuilding->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnCancelBuilding);
	OpenResources->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnOpenResourcs);
	HideResources->OnClicked.AddUniqueDynamic(this, &UGameplayView::OnHideResources);

	gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->UIManager->GameplayView = this;

}


#pragma region Public Functions
void UGameplayView::SetAllVisibility(bool state)
{
	if (state)
		AllUnits->SetVisibility(ESlateVisibility::Visible);
	else
		AllUnits->SetVisibility(ESlateVisibility::Hidden);
}
void UGameplayView::SetBuildingState(bool state)
{
	if (state)
	{
		BuildUI->SetVisibility(ESlateVisibility::Hidden);
		Building->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		BuildUI->SetVisibility(ESlateVisibility::Visible);
		Building->SetVisibility(ESlateVisibility::Hidden);
	}

	gameMode->GameManager->InBuildingMode = state;
	gameMode->GameManager->ShowGrid(state);
}
void UGameplayView::RefreshResourcesUI()
{
	RawWoodAmount->SetText(FText::FromString(FString::FromInt(gameMode->GameManager->RawWoodAmount)));
	WoodAmount->SetText(FText::FromString(FString::FromInt(gameMode->GameManager->WoodAmount)));
	StoneAmount->SetText(FText::FromString(FString::FromInt(gameMode->GameManager->StoneAmount)));
	FoodAmount->SetText(FText::FromString(FString::FromInt(gameMode->GameManager->FoodAmount)));
}
#pragma endregion

#pragma region Callbacks
void UGameplayView::OnBuildButtonClick()
{
	GameplayUI->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnBackButtonClick()
{
	GameplayUI->SetVisibility(ESlateVisibility::Visible);
	BuildUI->SetVisibility(ESlateVisibility::Hidden);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnCancelBuilding()
{
	SetBuildingState(false);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnHouseButtonClick()
{
	gameMode->GameManager->ToBuild = EBuildingType::House;
	SetBuildingState(true);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnWoodMillButtonClick()
{
	gameMode->GameManager->ToBuild = EBuildingType::WoodMill;
	SetBuildingState(true);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnTowerButtonClick()
{
	gameMode->GameManager->ToBuild = EBuildingType::Tower;
	SetBuildingState(true);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnOpenResourcs()
{
	RefreshResourcesUI();
	
	Resources->SetVisibility(ESlateVisibility::Visible);
	OpenResources->SetVisibility(ESlateVisibility::Hidden);
	gameMode->AudioManager->PlayClickAudio();
}
void UGameplayView::OnHideResources()
{
	OpenResources->SetVisibility(ESlateVisibility::Visible);
	Resources->SetVisibility(ESlateVisibility::Hidden);
	gameMode->AudioManager->PlayClickAudio();
}

#pragma endregion


