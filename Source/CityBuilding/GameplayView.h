// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameplayView.generated.h"

class AGameManager;
class ACityBuildingGameModeBase;

UCLASS()
class CITYBUILDING_API UGameplayView : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

#pragma region Bound TO Unreal
public:
	UPROPERTY(meta = (BindWidget)) UPanelWidget* AllUnits;
	UPROPERTY(meta = (BindWidget)) UPanelWidget* GameplayUI;
	UPROPERTY(meta = (BindWidget)) UPanelWidget* BuildUI;
	UPROPERTY(meta = (BindWidget)) UPanelWidget* Building;
	UPROPERTY(meta = (BindWidget)) UButton* BuildButton;
	UPROPERTY(meta = (BindWidget)) UButton* BackButton;
	UPROPERTY(meta = (BindWidget)) UButton* CancelBuilding;
	UPROPERTY(meta = (BindWidget)) UButton* HouseButton;
	UPROPERTY(meta = (BindWidget)) UButton* TowerButton;
	UPROPERTY(meta = (BindWidget)) UButton* WoodMillButton;
	UPROPERTY(meta = (BindWidget)) UTextBlock* WoodAmount;
	UPROPERTY(meta = (BindWidget)) UTextBlock* RawWoodAmount;
	UPROPERTY(meta = (BindWidget)) UTextBlock* StoneAmount;
	
	UFUNCTION() void OnBuildButtonClick();
	UFUNCTION()	void OnBackButtonClick();
	UFUNCTION() void OnCancelBuilding();
	UFUNCTION()	void OnHouseButtonClick();
	UFUNCTION() void OnTowerButtonClick();
	UFUNCTION() void OnWoodMillButtonClick();
#pragma endregion

#pragma region Public Functions
public:
	void SetAllVisibility(bool state);
#pragma endregion

#pragma region Private Variables
private:
	ACityBuildingGameModeBase* gameMode;
#pragma endregion
#pragma region Private Functions
	void SetBuildingState(bool state);
#pragma endregion

public:
	void RefreshResourcesUI();

};
