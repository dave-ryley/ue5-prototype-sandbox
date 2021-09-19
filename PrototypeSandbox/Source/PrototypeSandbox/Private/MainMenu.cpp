// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"

#include "ServerRow.h"
#include "Components/EditableText.h"

void UMainMenu::SetServerList(const TArray<FServerData>& ServerData)
{
	UE_LOG(LogTemp, Warning, TEXT("In SetServerList"));
	ServerListBox->ClearChildren();

	for (const auto& Data : ServerData)
	{
		auto* ServerRow = CreateWidget<UServerRow>(this, ServerRowClass);
		ServerRow->Setup(Data);
		ServerRow->SetOnClickedCallback([&](UServerRow* SelectedRow)
		{
			if (CurrentlySelectedRow)
			{
				CurrentlySelectedRow->SetIsSelected(false);
			}
			CurrentlySelectedRow = SelectedRow;
			CurrentlySelectedRow->SetIsSelected(true);
		});
		ServerListBox->AddChild(ServerRow);
	}
	ServerListBox->InvalidateLayoutAndVolatility();
}

FString UMainMenu::GetHostServerName() const
{
	if (!ensure(ServerNameEditableText != nullptr)) return "";

	return ServerNameEditableText->GetText().ToString();
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;
	if (!ensure(MainMenu != nullptr)) return false;
	if (!ensure(JoinMenu != nullptr)) return false;
	if (!ensure(JoinBackButton != nullptr)) return false;
	if (!ensure(HostBackButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(ServerListBox != nullptr)) return false;
	if (!ensure(ServerRowClass != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	HostBackButton->OnClicked.AddDynamic(this, &UMainMenu::CloseSubMenu);
	JoinBackButton->OnClicked.AddDynamic(this, &UMainMenu::CloseSubMenu);
	HostMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHostMenu);
	JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	return true;
}

void UMainMenu::HostServer()
{
	if (!ensure(MenuInterface != nullptr)) return;

	MenuInterface->Host();
}

void UMainMenu::JoinServer()
{
	if (!ensure(MenuInterface != nullptr)) return;

	if (SelectedSearchResult != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected Server %s."), *SelectedSearchResult->GetSessionIdStr());
		MenuInterface->Join(*SelectedSearchResult);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectedRow not set."));
	}
}

void UMainMenu::OpenHostMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(HostMenu != nullptr)) return;

	MenuSwitcher->SetActiveWidget(HostMenu);
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	MenuInterface->FindSessions();
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CloseSubMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(MainMenu != nullptr)) return;
	
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::QuitGame()
{
	if (!ensure(MenuInterface != nullptr)) return;
	MenuInterface->QuitGame();
}
