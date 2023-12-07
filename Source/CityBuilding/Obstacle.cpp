// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "CityBuildingGameModeBase.h"
#include "GameManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::DestroyIfEnoughResources()
{
	bool hasEnoughResources = true;

	for(auto resource : Resources)
	{
		if(gameMode->GameManager->HasResource(resource.ResourceType, - resource.Amount) == false)
		{
			UE_LOG(LogTemp, Display, TEXT("%s"), *UEnum::GetValueAsString(resource.ResourceType));

			hasEnoughResources = false;
			break;
		}
	}


	if(hasEnoughResources)
	{
		for(auto resource : Resources)
		{
			gameMode->GameManager->IncreaseResource(resource.ResourceType, resource.Amount);
		}

		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(" Not Enough Resources"));
	}


}

