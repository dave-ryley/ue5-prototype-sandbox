// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"

AMultiplayerTutorialGameMode::AMultiplayerTutorialGameMode()
{
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerController(TEXT("/Game/Maps/LevelSelect/BP_PlayerControllerBase"));
	if (PlayerController.Class != nullptr)
	{
		PlayerControllerClass = PlayerController.Class;
	}
}

void AMultiplayerTutorialGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AMultiplayerTutorialGameMode game mode loaded"));
}
