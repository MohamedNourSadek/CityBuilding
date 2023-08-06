// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUIManager.h"
#include "GameManager.h"

void UGameplayUIManager::NativeConstruct()
{
	Super::Construct();

	BuildButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnBuildButtonClick);
	BackButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnBackButtonClick);
	HouseButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnHouseButtonClick);
	CancelBuilding->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnCancelBuilding);


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
}

void UGameplayUIManager::OnCancelBuilding()
{
	Building->SetVisibility(ESlateVisibility::Hidden);
	BuildUI->SetVisibility(ESlateVisibility::Visible);
}


