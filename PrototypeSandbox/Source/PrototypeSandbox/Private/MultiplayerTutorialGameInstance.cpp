// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"
#include "InGameMenu.h"


void UMultiplayerTutorialGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	Menu->SetMenuInterface(this);
	Menu->Setup();
}

void UMultiplayerTutorialGameInstance::InGameLoadMenu()
{
	if (!ensure(InGameMenuClass != nullptr)) return;
	InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	if (!ensure(InGameMenu != nullptr)) return;
	InGameMenu->SetMenuInterface(this);
	InGameMenu->Setup();
}

void UMultiplayerTutorialGameInstance::Host()
{
	auto* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	auto* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/Maps/MultiplayerTutorial/Map_MultiplayerTutorial?listen");
}

void UMultiplayerTutorialGameInstance::Join(const FString& Address)
{
	auto* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	auto* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UMultiplayerTutorialGameInstance::Quit()
{
	auto* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
