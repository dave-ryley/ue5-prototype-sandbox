// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	NumPlayers.IncrementExchange();

	if (NumPlayers.Load() == 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("Reached 2 players"));
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	
	NumPlayers.DecrementExchange();
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("ALobbyGameMode game mode loaded"));
}
