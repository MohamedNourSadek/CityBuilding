// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "CityBuildingGameModeBase.h"
#include "CityPlayerPawn.h"
#include "GameplayUIManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	gameplayUIManager = CreateWidget<UGameplayUIManager>(GetGameInstance(), gameplayUIclass);
	gameplayUIManager->AddToViewport();

	ACityBuildingGameModeBase* gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->GameManager = this;

	mainPlayer = Cast<ACityPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

