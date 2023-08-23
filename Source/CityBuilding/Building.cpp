// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(1,1,0));
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(animatingStartAnim)
	{
		SetActorScale3D(GetActorScale3D() + FVector(0,0,DeltaTime*AnimationSpeed));

		if(GetActorScale3D().Z >= 1)
			animatingStartAnim = false;
	}
}

