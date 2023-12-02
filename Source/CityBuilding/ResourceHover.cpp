// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHover.h"

#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

void UResourceHover::SetUIUp(const TArray<FResource>& resources)
{
	for(auto oldElement : elements)
	{
		oldElement->RemoveFromParent();
	}

	elements.Empty();

	for(auto resource : resources)
	{
		const FString elementName = UEnum::GetValueAsString(resource.ResourceType);
		const auto myNewElement =  NewObject<UHoverResourceElement>(ElementPrototype);

		const auto elementNameText = NewObject<UTextBlock>(ElementPrototype->ElementName);
		const auto elementAmountText = NewObject<UTextBlock>(ElementPrototype->ElementAmount);

		auto slot1 = myNewElement->AddChildToHorizontalBox(elementAmountText);
		auto slot2 = myNewElement->AddChildToHorizontalBox(elementNameText);

		slot1->SetHorizontalAlignment(HAlign_Center);
		slot1->SetVerticalAlignment(VAlign_Center);
		slot1->SetPadding(FMargin(5));

		slot2->SetHorizontalAlignment(HAlign_Center);
		slot2->SetVerticalAlignment(VAlign_Center);		
		slot2->SetPadding(FMargin(5));

		myNewElement->ElementName = elementNameText;
		myNewElement->ElementAmount = elementAmountText;

		myNewElement->SetUpElement(elementName, resource.Amount);

		auto slot = ElementsParent->AddChildToVerticalBox(myNewElement);
		slot->SetHorizontalAlignment(HAlign_Center);
		slot->SetVerticalAlignment(VAlign_Center);
		slot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
		elements.Add(myNewElement);

		UE_LOG(LogTemp, Display, TEXT("%d"), resource.Amount);
	}
}
