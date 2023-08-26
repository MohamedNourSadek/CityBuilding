// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "CityPlayerPawn.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABuilding::ABuilding()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	SetActorScale3D(FVector(0,0,0));

	mainPlayer = Cast<ACityPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	buildingOptions = GetComponentByClass<UChildActorComponent>();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TotalTimeSinceStartUp+= DeltaTime;
	
	if(animatingStartAnim)
	{
		float timeValue = TotalTimeSinceStartUp*AnimationSpeed;
		float value = curve.ExternalCurve->GetFloatValue(timeValue);
		SetActorScale3D(FVector(1,1,1)* value);

		if(TotalTimeSinceStartUp >= 1)
			animatingStartAnim = false;
	}

	if(mainPlayer != nullptr)
	{
		FRotator rotator = UKismetMathLibrary::FindLookAtRotation(buildingOptions->GetComponentLocation(),
			mainPlayer->cameraComponent->GetComponentLocation());

		buildingOptions->SetWorldRotation(rotator);
	}

}

