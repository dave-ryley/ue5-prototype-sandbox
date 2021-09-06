// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.h"


void UMultiplayerTutorialGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;

	Menu->SetMenuInterface(this);
	Menu->Setup();
}

void UMultiplayerTutorialGameInstance::Host()
{
	auto* engine = GetEngine();
	if (!ensure(engine != nullptr)) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	auto* world = GetWorld();
	if (!ensure(world != nullptr)) return;

	world->ServerTravel("/Game/Maps/MultiplayerTutorial/Map_MultiplayerTutorial?listen");
}

void UMultiplayerTutorialGameInstance::Join(const FString& Address)
{
	auto* engine = GetEngine();
	if (!ensure(engine != nullptr)) return;

	engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	auto* pController = GetFirstLocalPlayerController();
	if (!ensure(pController != nullptr)) return;

	pController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
