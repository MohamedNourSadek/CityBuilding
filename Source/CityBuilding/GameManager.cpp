// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

#include "GameplayUIManager.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

