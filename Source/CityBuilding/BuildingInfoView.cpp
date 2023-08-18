// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInfoView.h"
#include "GameManager.h"
#include "CityBuildingGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UBuildingInfoView::NativeConstruct()
{
	Super::Construct();
	CloseButton->OnClicked.AddDynamic(this, &UBuildingInfoView::OnCloseButtonPressed);
}

void UBuildingInfoView::OnCloseButtonPressed()
{
	const ACityBuildingGameModeBase* gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	gameMode->GameplayView->SetAllVisibility(true);
	gameMode->GameManager->IsBuildingInfoOpen = false;

	this->RemoveFromParent();
	this->MarkAsGarbage();
}