// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameplayUIManager.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API UGameplayUIManager : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget)) UButton* BuildButton;
	UPROPERTY(EditAnywhere) TArray<AActor*> gridCubes;


	void OnBuildButtonClick();

};
