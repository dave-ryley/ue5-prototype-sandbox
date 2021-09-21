// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayerTutorialGameMode.h"
#include "LobbyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPESANDBOX_API ALobbyGameMode : public AMultiplayerTutorialGameMode
{
	GENERATED_BODY()
public:

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void BeginPlay() override;
private:
	TAtomic<uint8_t> NumPlayers;
};
