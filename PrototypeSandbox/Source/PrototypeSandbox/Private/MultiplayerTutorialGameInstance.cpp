// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerTutorialGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "MainMenu.h"
#include "InGameMenu.h"

const static FName GSession_Name = TEXT("My Session Game");

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
		SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMultiplayerTutorialGameInstance::OnJoinSessionComplete);
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
		const auto ExistingSession = SessionInterface->GetNamedSession(GSession_Name);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(ExistingSession->SessionName);
			return;
		}
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = 2;
		SessionSettings.bShouldAdvertise = true;
		SessionInterface->CreateSession(0, GSession_Name, SessionSettings);
	}
}

void UMultiplayerTutorialGameInstance::Join(const FOnlineSessionSearchResult& Result)
{
	auto* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Joining %s"), *Result.GetSessionIdStr()));
	if (SessionInterface->JoinSession(0, GSession_Name, Result))
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Successfully Joined %s"), *Result.GetSessionIdStr()));
	}
	else
	{
		Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, FString::Printf(TEXT("Failed to Joined %s"), *Result.GetSessionIdStr()));
	}
}

void UMultiplayerTutorialGameInstance::QuitGame()
{
	auto* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}

void UMultiplayerTutorialGameInstance::OnSessionCreated(const FName SessionName, const bool IsSuccessful)
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

void UMultiplayerTutorialGameInstance::OnSessionDestroyed(const FName SessionName, const bool IsSuccessful)
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

void UMultiplayerTutorialGameInstance::OnFindSessionsComplete(const bool IsSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Found sessions %s"), (IsSuccessful ? TEXT("success") : TEXT("failed")));

	if (IsSuccessful && SessionSearch.IsValid())
	{
		Menu->SetServerList(SessionSearch->SearchResults);
	}
}

void UMultiplayerTutorialGameInstance::OnJoinSessionComplete(FName SessionName,
	EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinSession Result: %d"), Result);
	if (Result == EOnJoinSessionCompleteResult::Type::Success)
	{
		FString Address;
		SessionInterface->GetResolvedConnectString(SessionName, Address);
 
		GetFirstLocalPlayerController()->ClientTravel(Address, TRAVEL_Absolute);
	}
}
