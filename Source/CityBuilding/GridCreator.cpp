// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCreator.h"

// Sets default values
AGridCreator::AGridCreator()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGridCreator::BeginPlay()
{
	Super::BeginPlay();
}

void AGridCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridCreator::CreateGrid()
{
	UE_LOG(LogTemp, Display, TEXT("Test"));

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			FVector position = GetActorLocation() + FVector(i * (100 + spacing), j * (100 + spacing), 0);
			GetWorld()->SpawnActor<AActor>(prototype, position, GetActorRotation());
		}
	}

}

