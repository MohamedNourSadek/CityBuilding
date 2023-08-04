// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCreator.generated.h"

UCLASS()
class CITYBUILDING_API AGridCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	AGridCreator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		int width = 5;
	UPROPERTY(EditAnywhere)
		int height = 5;
	UPROPERTY(EditAnywhere)
		int spacing = 20;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> prototype;
	UPROPERTY(EditAnywhere)
		int unitSize = 1;
	UPROPERTY(EditAnywhere)
		float depth = 0.1;


	UFUNCTION(CallInEditor)
		void CreateGrid();
};
