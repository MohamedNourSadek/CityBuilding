// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUIManager.h"

bool UGameplayUIManager::Initialize()
{
	Super::Initialize();

	BuildButton->OnClicked.AddDynamic(this, &UGameplayUIManager::OnBuildButtonClick);

	return true;
}

void UGameplayUIManager::OnBuildButtonClick()
{
	UE_LOG(LogTemp, Error, TEXT("On Build Pressed"));
}

