// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HoverResourceElement.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "ResourceHover.generated.h"

UENUM()
enum EResourceType
{
	Wood UMETA(DisplayName = "Wood"),
	Stone UMETA(DisplayName = "Stone"),
	Food UMETA(DisplayName = "Food")
};

USTRUCT()
struct FResource
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<EResourceType> ResourceType;
	UPROPERTY(EditAnywhere)
	int Amount;

	FResource()
	{
		ResourceType = EResourceType::Wood;
		Amount = 0;
	}

	FResource(EResourceType resourceType)
	{
		ResourceType = resourceType;
		Amount = 0;
	}

	FResource(EResourceType resourceType, int amount) : ResourceType(resourceType)
	{
		Amount = amount;
	}
};


UCLASS()
class CITYBUILDING_API UResourceHover : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUIUp(const TArray<FResource>& resources);

	UPROPERTY(meta = (BindWidget)) UVerticalBox* ElementsParent;
	UPROPERTY(meta = (BindWidget)) UHoverResourceElement* ElementPrototype;


private:
	TArray<UHorizontalBox*> elements;
};
