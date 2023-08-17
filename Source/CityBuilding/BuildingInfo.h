// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BuildingInfo.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API UBuildingInfo : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget)) UButton* CloseButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnCloseButtonPressed();

};
