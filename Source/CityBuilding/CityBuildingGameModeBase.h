// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayView.h"
#include "UIManager.h"
#include "GameFramework/GameModeBase.h"
#include "CityBuildingGameModeBase.generated.h"

UCLASS()
class CITYBUILDING_API ACityBuildingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


public:
	AGameManager* GameManager;
	AUIManager* UIManager;


};
