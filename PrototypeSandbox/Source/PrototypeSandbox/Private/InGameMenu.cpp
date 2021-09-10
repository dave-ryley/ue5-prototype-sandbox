// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(ContinueButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;

	ContinueButton->OnClicked.AddDynamic(this, &UInGameMenu::Continue);
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::Quit);

	return true;
}

void UInGameMenu::Continue()
{
	TearDown();
}

void UInGameMenu::Quit()
{
	auto* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	auto* PlayerController = World->GetFirstPlayerController();
	const FString Address = "/Game/Maps/LevelSelect/Map_LevelSelect";

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
