// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityBuildingGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "BuildingInfoView.generated.h"

UCLASS()
class CITYBUILDING_API UBuildingInfoView : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UFUNCTION() void OnCloseButtonPressed();

	ACityBuildingGameModeBase* gameMode;


public:
	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;
	UPROPERTY(meta = (BindWidget)) UImage* BuildingImage;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Title;
	UPROPERTY(meta = (BindWidget)) UTextBlock* Description;

	void SetUI(EBuildingType buildingType);

};
