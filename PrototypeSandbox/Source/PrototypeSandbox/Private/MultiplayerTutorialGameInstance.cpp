// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MainMenu.h"
#include "InGameMenu.h"

const static FName GSESSION_NAME = "My Session Game";

void UMultiplayerTutorialGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Initializing UMultiplayerTutorialGameInstance"));

	IOnlineSubsystem* Oss = IOnlineSubsystem::Get();

	if (Oss)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got OnlineSubsystem %s"), *Oss->GetSubsystemName().ToString());
		SessionInterface = Oss->GetSessionInterface();
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerTutorialGameInstance::OnSessionCreated);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerTutorialGameInstance::OnSessionDestroyed);
		SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerTutorialGameInstance::OnFindSessionsComplete);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found no Online Subsystem"), *Oss->GetSubsystemName().ToString());
	}
}

void UMultiplayerTutorialGameInstance::FindSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->bIsLanQuery = true;
		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

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
	if (SessionInterface.IsValid())
	{
		const auto ExistingSession = SessionInterface->GetNamedSession(GSESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(ExistingSession->SessionName);
			return;
		}
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, GSESSION_NAME, SessionSettings);
	}
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

void UMultiplayerTutorialGameInstance::QuitGame()
{
	auto* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMultiplayerTutorialGameInstance::OnSessionCreated(FName SessionName, bool IsSuccessful)
{
	if (IsSuccessful)
	{
		auto* Engine = GetEngine();
		if (!ensure(Engine != nullptr)) return;

		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

		auto* World = GetWorld();
		if (!ensure(World != nullptr)) return;

		World->ServerTravel("/Game/Maps/MultiplayerTutorial/Map_MultiplayerTutorial?listen");
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session: %s"), *SessionName.ToString());
	}
}

void UMultiplayerTutorialGameInstance::OnSessionDestroyed(FName SessionName, bool IsSuccessful)
{
	if (IsSuccessful)
	{
		Host();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to destroy existing session: %s"), *SessionName.ToString());
	}
}

void UMultiplayerTutorialGameInstance::OnFindSessionsComplete(bool IsSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Found sessions %s"), (IsSuccessful ? TEXT("success") : TEXT("failed")));

	if (IsSuccessful && SessionSearch.IsValid())
	{
		TArray<FString> ServerNames;
		ServerNames.Reserve(SessionSearch->SearchResults.Num());
		for (auto&& Result : SessionSearch->SearchResults)
		{
			ServerNames.Push(Result.GetSessionIdStr());
		}
		Menu->SetServerList(ServerNames);
	}
}
