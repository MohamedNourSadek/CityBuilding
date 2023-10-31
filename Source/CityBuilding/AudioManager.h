// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/AmbientSound.h"
#include "AudioManager.generated.h"

UCLASS()
class CITYBUILDING_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere) USoundBase* ClickAudio;
	UPROPERTY(EditAnywhere) TArray<USoundBase*> MusicFiles;
	UPROPERTY(EditAnywhere) AAmbientSound* MusicAudioPlayer;
	

private:
	int currentlyPlayed = 0;

public:
	void PlayClickAudio();

	UFUNCTION()
	void PlayARandomAmbientMusic();
};
