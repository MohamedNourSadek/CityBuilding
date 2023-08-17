// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayUIManager.h"
#include "GameFramework/GameModeBase.h"
#include "CityBuildingGameModeBase.generated.h"

class AGameManager;

UCLASS()
class CITYBUILDING_API ACityBuildingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	AGameManager* GameManager;
	UGameplayUIManager* GameplayUIManager;
};
