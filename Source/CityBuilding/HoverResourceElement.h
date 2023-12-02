// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "HoverResourceElement.generated.h"

/**
 * 
 */
UCLASS()
class CITYBUILDING_API UHoverResourceElement : public UHorizontalBox
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere) UTextBlock* ElementName;
	UPROPERTY(EditAnywhere) UTextBlock* ElementAmount;


	void SetUpElement(FString elementName, int elementAmount);

};
