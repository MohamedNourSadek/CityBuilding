// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "CityBuildingGameModeBase.h"
#include "Kismet/GameplayStatics.h"

AAudioManager::AAudioManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->AudioManager = this;
}

void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::PlayClickAudio()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),
	ClickAudio,
	GetActorLocation(),
	GetActorRotation(),
	1,1,0);
}


