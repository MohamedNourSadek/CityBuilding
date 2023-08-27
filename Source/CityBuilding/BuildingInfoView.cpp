// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInfoView.h"
#include "GameManager.h"
#include "CityBuildingGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UBuildingInfoView::NativeConstruct()
{
	Super::Construct();

	gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	CloseButton->OnClicked.AddDynamic(this, &UBuildingInfoView::OnCloseButtonPressed);
}
void UBuildingInfoView::SetUI(EBuildingType buildingType)
{
	BuildingImage->SetBrushFromTexture(gameMode->UIManager->BuildingsIcons[buildingType]);
	Title->SetText(FText::FromString(gameMode->UIManager->BuildingTitles[buildingType]));
	Description->SetText(FText::FromString(gameMode->UIManager->BuildingDes[buildingType]));
}
void UBuildingInfoView::OnCloseButtonPressed()
{
	if(gameMode != nullptr)
	{
		gameMode->UIManager->GameplayView->SetAllVisibility(true);
		gameMode->UIManager->IsBuildingInfoOpen = false;
		this->RemoveFromParent();
		this->MarkAsGarbage();
		gameMode->AudioManager->PlayClickAudio();
	}
}