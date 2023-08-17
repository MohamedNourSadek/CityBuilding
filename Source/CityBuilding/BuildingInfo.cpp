// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInfo.h"

#include "CityBuildingGameModeBase.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

void UBuildingInfo::NativeConstruct()
{
	Super::Construct();
	CloseButton->OnClicked.AddDynamic(this, &UBuildingInfo::OnCloseButtonPressed);
}

void UBuildingInfo::OnCloseButtonPressed()
{
	const ACityBuildingGameModeBase* gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	gameMode->GameplayUIManager->SetAllVisibility(true);
	gameMode->GameManager->IsBuildingInfoOpen = false;

	this->RemoveFromParent();
	this->MarkAsGarbage();

}

