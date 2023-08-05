// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayUIManager.h"


void UGameplayUIManager::NativeConstruct()
{
	Super::Construct();
	BuildButton->OnClicked.AddUniqueDynamic(this, &UGameplayUIManager::OnBuildButtonClick);
}


void UGameplayUIManager::OnBuildButtonClick() 
{
	UE_LOG(LogTemp, Error, TEXT("On Build Pressed"));
}

