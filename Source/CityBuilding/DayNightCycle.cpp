// Fill out your copyright notice in the Description page of Project Settings.


#include "DayNightCycle.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ADayNightCycle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADayNightCycle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(light != nullptr)
		light->AddActorWorldRotation(FRotator(daySpeed* DeltaTime,0,0));

	if(sun !=nullptr)
	{
		FOutputDeviceNull ar;
		sun->CallFunctionByNameWithArguments(TEXT("UpdateSunDirection"), ar, NULL, true);
	}

	
}

