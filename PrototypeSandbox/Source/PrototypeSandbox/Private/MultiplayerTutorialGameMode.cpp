// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"

AMultiplayerTutorialGameMode::AMultiplayerTutorialGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> playerController(TEXT("/Game/Maps/LevelSelect/BP_PlayerControllerBase"));
	if (playerController.Class != nullptr)
	{
		PlayerControllerClass = playerController.Class;
	}
}

void AMultiplayerTutorialGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AMultiplayerTutorialGameMode game mode loaded"));
}
