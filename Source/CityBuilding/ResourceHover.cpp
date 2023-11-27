// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceHover.h"

void UResourceHover::SetUIUp(const TArray<FResource>& resources)
{
	for(auto resource : resources)
	{
		UE_LOG(LogTemp, Display, TEXT("%d"), resource.Amount);
	}
}
