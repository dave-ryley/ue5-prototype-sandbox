// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

void UMainMenu::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	MenuInterface = NewMenuInterface;
}

void UMainMenu::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	UWorld* world = GetWorld();
	if (!ensure(world != nullptr)) return;
	APlayerController* playerController = world->GetFirstPlayerController();
	
	FInputModeUIOnly mode;
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	mode.SetWidgetToFocus(TakeWidget());

	playerController->SetInputMode(mode);
	playerController->SetShowMouseCursor(true);
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	if (!ensure(InWorld != nullptr)) return;
	APlayerController* playerController = InWorld->GetFirstPlayerController();

	FInputModeGameOnly mode;
	mode.SetConsumeCaptureMouseDown(true);

	playerController->SetInputMode(mode);
	playerController->SetShowMouseCursor(false);
	RemoveFromViewport();
}

bool UMainMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ensure(HostButton != nullptr)) return false;
	if (!ensure(JoinButton != nullptr)) return false;

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

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

	MenuInterface->Join("localhost");
}