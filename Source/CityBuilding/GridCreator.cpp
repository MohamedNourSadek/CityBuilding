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

void AGridCreator::Button()
{
	UE_LOG(LogTemp, Display, TEXT("Test"));
}

