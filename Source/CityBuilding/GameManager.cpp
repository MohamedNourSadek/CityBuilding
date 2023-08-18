// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "CityBuildingGameModeBase.h"
#include "CityPlayerPawn.h"
#include "GameplayView.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AGameManager::Tick(float DeltaTime)
{
}
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	ACityBuildingGameModeBase* gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	MainPlayer = Cast<ACityPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	gameMode->GameManager = this;
}
void AGameManager::ShowGrid(bool state)
{
	TArray<AActor*> actors;

	Grid->GetAttachedActors(actors, true);

	for(int i =0; i < actors.Num(); i++)
	{
		actors[i]->SetActorHiddenInGame(!state);
	}
}

