// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameplayUIManager.generated.h"

class AGameManager;

UCLASS()
class CITYBUILDING_API UGameplayUIManager : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget)) UPanelWidget* GameplayUI;
	UPROPERTY(meta = (BindWidget)) UPanelWidget* BuildUI;
	UPROPERTY(meta = (BindWidget)) UPanelWidget* Building;
	UPROPERTY(meta = (BindWidget)) UButton* BuildButton;
	UPROPERTY(meta = (BindWidget)) UButton* HouseButton;
	UPROPERTY(meta = (BindWidget)) UButton* BackButton;
	UPROPERTY(meta = (BindWidget)) UButton* CancelBuilding;

	AGameManager* GameManager;


	void GetGameManager();

	UFUNCTION()
	void OnBuildButtonClick();

	UFUNCTION()
	void OnBackButtonClick();

	UFUNCTION()
	void OnHouseButtonClick();

	UFUNCTION()
	void OnCancelBuilding();
};
