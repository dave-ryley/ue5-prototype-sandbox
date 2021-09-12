// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/WidgetSwitcher.h"

#include "ServerRow.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;
	if (!ensure(QuitButton != nullptr)) return false;
	if (!ensure(MainMenu != nullptr)) return false;
	if (!ensure(JoinMenu != nullptr)) return false;
	if (!ensure(BackButton != nullptr)) return false;
	if (!ensure(JoinMenuButton != nullptr)) return false;
	if (!ensure(ServerListBox != nullptr)) return false;
	if (!ensure(ServerRowClass != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
	BackButton->OnClicked.AddDynamic(this, &UMainMenu::CloseJoinMenu);
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

	// TODO empty string handling
	// MenuInterface->Join(ServerAddressTextBox->GetText().ToString());
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(MenuSwitcher != nullptr)) return;
	if (!ensure(JoinMenu != nullptr)) return;

	auto* ServerRow = CreateWidget<UServerRow>(this, ServerRowClass);
	ServerRow->SetServerName(FText::FromString(TEXT("Dave's Fancy Server")));
	ServerListBox->AddChild(ServerRow);
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::CloseJoinMenu()
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
