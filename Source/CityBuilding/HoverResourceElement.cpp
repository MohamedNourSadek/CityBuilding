// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverResourceElement.h"


void UHoverResourceElement::SetUpElement(FString elementName, int elementAmount)
{
	ElementName->SetText(FText::FromString(elementName));

	ElementAmount->SetText(FText::FromString(FString::FromInt(FMath::Abs(elementAmount))));
}


