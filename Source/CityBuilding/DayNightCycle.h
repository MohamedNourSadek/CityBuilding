// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DirectionalLight.h"
#include "Misc/OutputDeviceNull.h"
#include "DayNightCycle.generated.h"

UCLASS()
class CITYBUILDING_API ADayNightCycle : public AActor
{
	GENERATED_BODY()
	
public:	
	ADayNightCycle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Day Night Control") AActor* sun;
	UPROPERTY(EditAnywhere, Category = "Day Night Control") ADirectionalLight* light;
	UPROPERTY(EditAnywhere, Category = "Day Night Control") float daySpeed;
};
