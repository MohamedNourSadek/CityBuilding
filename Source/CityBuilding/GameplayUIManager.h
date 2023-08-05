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

	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere) TArray<AActor*> gridCubes;
	UPROPERTY(meta = (BindWidget)) UButton* BuildButton;

	UFUNCTION()
	void OnBuildButtonClick();
};
