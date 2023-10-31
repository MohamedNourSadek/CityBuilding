// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"

#include "CityBuildingGameModeBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

AAudioManager::AAudioManager()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
	Cast<ACityBuildingGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->AudioManager = this;

	FScriptDelegate scriptDelegate;
	scriptDelegate.BindUFunction(this, "PlayARandomAmbientMusic");
	MusicAudioPlayer->GetAudioComponent()->OnAudioFinished.Add(scriptDelegate);

	PlayARandomAmbientMusic();
}
void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAudioManager::PlayClickAudio()
{
	UGameplayStatics::PlaySoundAtLocation(
	GetWorld(),
	ClickAudio,
	GetActorLocation(),
	GetActorRotation(),
	1,1,0);
}

void AAudioManager::PlayARandomAmbientMusic()
{
	
	int newClip = 0;

	while(newClip == currentlyPlayed)
		newClip = FMath::RandRange(0,MusicFiles.Num() - 1);

	currentlyPlayed = newClip;
	
	UE_LOG(LogTemp, Display, TEXT("Playing a new Song : %s"), *MusicFiles[newClip]->GetName());

	
	MusicAudioPlayer->GetAudioComponent()->Sound = MusicFiles[newClip];
	MusicAudioPlayer->Play();
}


