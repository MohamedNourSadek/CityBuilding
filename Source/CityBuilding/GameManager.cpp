// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "CityBuildingGameModeBase.h"
#include "CityPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameManager::Tick(float DeltaTime)
{
	if(MainPlayer != nullptr && BuildingOptionsObject != nullptr)
	{
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(
			BuildingOptionsObject->GetActorLocation(),
			MainPlayer->cameraComponent->GetComponentLocation());

		BuildingOptionsObject->SetActorRotation(rotator);
	}
}
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	MainPlayer = Cast<ACityPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	ACityBuildingGameModeBase* gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->GameManager = this;
}
void AGameManager::ShowGrid(bool state)
{
	TArray<AActor*> actors;

	Grid->GetAttachedActors(actors, true);

	for(int i =0; i < actors.Num(); i++)
	{
		if(actors[i] == nullptr)
			continue;

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
void AGameManager::MoveBuildingOptions(ABuilding* building)
{
	if(building == nullptr)
		BuildingOptionsObject->SetActorLocation(FVector(0,0,5000));
	else
		BuildingOptionsObject->SetActorLocation(building->GetActorLocation() + FVector(0,0, 830 + building->BuildingHeight));
}
void AGameManager::SetResource(EResourceType resource, int amount)
{
	if(ResourcesAvailable.Contains(resource))
	{
		ResourcesAvailable[resource] = amount;
	}
	else
	{
		ResourcesAvailable.Add(resource, amount);
	}
}
void AGameManager::IncreaseResource(EResourceType resource, int incrementAmount)
{
	if (ResourcesAvailable.Contains(resource))
	{
		ResourcesAvailable[resource] += incrementAmount;
	}
	else
	{
		ResourcesAvailable.Add(resource, incrementAmount);
	}
}
int AGameManager::GetResource(EResourceType resource)
{
	if (ResourcesAvailable.Contains(resource))
	{
		return ResourcesAvailable[resource];
	}
	else
	{
		ResourcesAvailable.Add(resource, 0);
		return 0;
	}
}
bool AGameManager::HasResource(EResourceType resource, int amountNeeded)
{
	if (ResourcesAvailable[resource] >= amountNeeded)
		return true;
	else
		return false;
}


