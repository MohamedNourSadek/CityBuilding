// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "CityBuildingGameModeBase.h"
#include "CityPlayerPawn.h"
#include "GameplayView.h"
#include "KismetAnimationLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

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
void AGameManager::SpawnBuilding(EBuildingType buildingType)
{
	TSubclassOf<AActor> buildingClass;

	if (buildingType == EBuildingType::House)
		buildingClass = HouseBuilding;
	else if (buildingType == EBuildingType::Tower)
		buildingClass = TowerBuilding;
	else if (buildingType == EBuildingType::WoodMill)
		buildingClass = WoodMill;

	const auto building = GetWorld()->SpawnActor(buildingClass, &HighLightObject->GetTransform());
	building->SetActorRotation(HighLightObject->GetActorRotation());
}
void AGameManager::SpawnLogs(const FVector& spawnLocation)
{
	SpawnPack(LogsPack, spawnLocation);
}
void AGameManager::SpawnStones(const FVector& spawnLocation)
{
	SpawnPack(StonesPack, spawnLocation);
}
void AGameManager::SpawnPack(TSubclassOf<AActor> object, const FVector& spawnLocation)
{
	FVector position = spawnLocation + FVector(0,0,200);
	FTimerHandle UnusedHandle;
	FTimerDelegate timerDel;
	
	SpawnVFXBoof(spawnLocation);

	timerDel.BindUFunction(this, FName("SpawnObject"), object, position);
	GetWorldTimerManager().SetTimer(UnusedHandle,timerDel , 0.5, false);
}
void AGameManager::SpawnObject(TSubclassOf<AActor> gameObject, FVector& position)
{
	GetWorld()->SpawnActor(gameObject, &position);
}

void AGameManager::SpawnVFXBoof(const FVector& spawnLocation)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(
		BoofVFX,
		this->GetDefaultAttachComponent(),
		FName(""),
		spawnLocation, this->GetActorRotation(),
		EAttachLocation::SnapToTarget,
		true);
}

