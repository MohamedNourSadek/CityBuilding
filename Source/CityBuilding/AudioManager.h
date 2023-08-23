// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	void PlayClickAudio();
};
