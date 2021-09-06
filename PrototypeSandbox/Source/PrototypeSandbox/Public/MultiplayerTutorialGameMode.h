// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerTutorialGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API AMultiplayerTutorialGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMultiplayerTutorialGameMode();

public:
	void BeginPlay() override;
};
